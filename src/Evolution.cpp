//  ---------------------------------------------------------------------------
//  This file is part of the 8-Bit SFX Generator
//	Copyright (C) 2022 Tobias Garpenhall <tobiasgarpenhall@gmail.com>
//
//	This program is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	(at your option) any later version.
//	
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//	GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with this program. If not, see <http://www.gnu.org/licenses/>.
//  ---------------------------------------------------------------------------

#define NATIVE_CODE
#include "Evolution.h"

using namespace IESFX;

Evolution::Evolution(double mutation_rate, double mutation_size)
	: _mutation_rate(mutation_rate), _mutation_size(mutation_size), _models(MODEL_SAMPLES)
{
	const auto random = util::random_vec<std::size_t>(std::size(examples));

	Interpreter interpreter;
	for (int i = 0; i < MODEL_SAMPLES; ++i)
		interpreter.read_str(&_models[i], examples[random[i]]);
}

void Evolution::add_model(const SoundGene& gene)
{
	_models.push_back(gene);
}

void Evolution::remove_model(const SoundGene& gene)
{
	_models.erase(std::remove_if( 
		_models.begin(), _models.end(), 
		[&gene](const SoundGene& model)
		{
			return gene == model;
		}), _models.end());
}

int Evolution::execute(size_t max_generations, double max_quality)
{
	if (_models.size() == 0)
		return EXIT_FAILURE;

	_active = true;

	_old_population = _population;

	_max_generations = max_generations;
	_max_quality = max_quality;

	_generations = 0;
	_quality = 0;

	initialize();

	while (_generations < _max_generations)
	{
		if (_shutdown)
			return EXIT_SUCCESS;

		std::for_each(std::execution::par_unseq, 
			_population.begin(), _population.end(),
			[this](SoundGene& candidate) // evaluate each candidate
			{
				evaluate(candidate);
			});

		// sort in descending order by fitness value to allow for a rank-based selection
		//
		std::sort(std::execution::par_unseq, 
			_proxy.begin(), _proxy.end(), 
			[](const Wrapper& lhs, const Wrapper& rhs)
			{
				return lhs > rhs;
			});

		double sum = std::accumulate(_proxy.begin(), _proxy.begin() + AVERAGE_SAMPLE, 0.0,
			[](const double val, const Wrapper& wrap)
			{ 
				return val + wrap.gene->_fitness;
			});

		_quality = (sum / AVERAGE_SAMPLE);

		if (_quality >= _max_quality)
			break;

		selection();

		crossover();

		mutation();

		++_generations;
	}

	// sort before finished
	//
	std::sort(std::execution::par_unseq,
		_population.begin(), _population.end(),
		[](const SoundGene& lhs, const SoundGene& rhs)
		{
			return lhs > rhs;
		});

	_proxy.clear();
	_models.clear();

	_generations = 0;
	_quality = 0;

	_active = false;

	return EXIT_SUCCESS;
}

void Evolution::initialize()
{
	_population = std::vector<SoundGene>(POPULATION_SIZE);
	_proxy = std::vector<Wrapper>(POPULATION_SIZE);

	_population.resize(POPULATION_SIZE - _models.size());

	std::for_each(
		std::execution::par_unseq,
		_population.begin(), _population.end(),
		[](SoundGene& gene)
		{
			gene.push({ 24, 14 }); // always volume on

			auto offsets = util::random_vec<RESID::reg8>(24);

			for (int s = util::random(1, 6); s > 0; --s)
			{
				for (int p = util::ropoke(); p > 0; --p)
				{
					gene.push({ offsets[p], util::rvpoke() });
				}
				gene.push({ util::rsample() });
				offsets = util::random_vec<RESID::reg8>(24);
			}
		});

	_population.insert(_population.end(), _models.begin(), _models.end());

	std::for_each(
		std::execution::par_unseq,
		_population.begin(), _population.end(),
		[this](SoundGene& gene)
		{
			const std::size_t i = std::distance(_population.data(), &gene);
			_proxy[i].gene = &gene;
		});
}

void Evolution::evaluate(SoundGene& candidate)
{
	candidate._fitness = 0;

	const double simi_mul = 2.75;
	const double smpl_mul = 0.25;
	const double time_mul = 0.15;

	// adjust fitness based on similiarity	TODO: FIX BIAS TOWARDS CERTAIN MODELS, EVERYONE HAS SIMILIARITY TO THE FIRST SEGMENT
	// 

	const auto c_range = candidate.range();

	if (c_range.size() == 0)
	{
		candidate._fitness = -DBL_MAX; // this candidate is invalid
		return;
	}

	std::for_each(_models.begin(), _models.end(),
		[&candidate, &simi_mul, &c_range](const SoundGene& model)
		{
			double score = 0.0;

			const auto m_range = model.range();
			const int min = std::min<int>((int)c_range.size(), (int)m_range.size());

			std::array<bool, 25> m_offsets;
			for (int si = 0; si < min; ++si) // do in reverse since only the last specified value matters
			{
				memset(m_offsets.data(), false, m_offsets.size());
				for (int j = std::get<1>(m_range[si]) - 1; j >= std::get<0>(m_range[si]); --j)
				{
					const Poke& m_poke = model.get<Poke>(j);
					if (!m_offsets[m_poke.get_offset()])
					{
						m_offsets[m_poke.get_offset()] = true;
						for (int k = std::get<1>(c_range[si]) - 1; k >= std::get<0>(c_range[si]); --k)
						{
							const Poke& c_poke = candidate.get<Poke>(k);
							if (m_poke.get_offset() == c_poke.get_offset())
							{
								const double val_diff = std::abs((int)m_poke.get_value() - (int)c_poke.get_value());
								const double val_ratio = 1.0 / (0.33 * val_diff + 1.0);

								score += val_ratio;

								break;
							}
						}
					}
				}

				const Sample& lhs_sample = model.get<Sample>(std::get<1>(m_range[si]));
				const Sample& rhs_sample = candidate.get<Sample>(std::get<1>(c_range[si]));

				const double smpl_diff = std::abs((int)lhs_sample.get_size() - (int)rhs_sample.get_size());
				const double smpl_ratio = 1.0 / (0.01 * smpl_diff + 1.0);

				score += smpl_ratio;
			}

			const double similarity = (score / model.size()); // not really the correct way, but yields better output???
			candidate._fitness += (similarity > 0.6 ? 0.6 / (similarity + 0.4) : similarity) * simi_mul;
		});

	// adjust fitness based on samples
	//
	int poke_count = 0;
	double time = 0.0;

	for (const Command::Ptr& command : candidate)
	{
		const CommandType type = command->get_type();

		switch (type)
		{
		case CT_Poke:
			++poke_count;
			break;
		case CT_Sample:
			{
				const Sample* sample = static_cast<const Sample*>(command.get());

				time += (double)util::time(sample->get_size());

				if (poke_count == 0)
					candidate._fitness += -smpl_mul; // no pokes given before sample is bad

				poke_count = 0;
			}
			break;
		}
	}

	candidate._fitness += -poke_count * smpl_mul; // pokes but no sample given is bad

	// adjust fitness based on length of audio
	//
	if (time < 0.2)
		candidate._fitness += -(0.2 / time) * time_mul;
	else if (time > 1.4)
		candidate._fitness += -(time / 1.4) * time_mul;
}

void Evolution::selection()
{
	std::for_each(
		std::execution::par_unseq,
		_proxy.begin(), _proxy.end(),
		[this](const Wrapper& wrap)
		{
			const std::size_t i = &wrap - _proxy.data(); // rank selection

			double chance = (i + 1) / (double)POPULATION_SIZE;

			if (util::random() + 0.4 <= chance) // +0.4 to give better chance for lower fitness to survive
				wrap.gene->_dead = true;
		});

	_population.erase(std::remove_if(
		std::execution::par_unseq,
		_population.begin(), _population.end(),
		[this](const SoundGene& gene)
		{
			return gene._dead && _population.size() > 2;
		}), _population.end());

	std::for_each(
		std::execution::par_unseq,
		_population.begin(), _population.end(),
		[this](SoundGene& gene)
		{
			const std::size_t i = std::distance(_population.data(), &gene);
			_proxy[i].gene = &gene;
		});

	_proxy.resize(_population.size());

	if (_population.size() % 2 != 0) // remove worst lone parent to keep things even for creating offspring
	{
		auto it = std::min_element(_proxy.begin(), _proxy.end());

		*it = _proxy.back();
		_proxy.pop_back();

		const std::size_t i = it->gene - _population.data();

		_population[i] = std::move(_population.back());
		_population.pop_back();
	}
}

void Evolution::crossover()
{
	const std::size_t elite = _population.size();
	_offspring_size = POPULATION_SIZE - elite;

	std::size_t spiral = 0;
	while (_population.size() != POPULATION_SIZE)
	{
		if (++spiral >= std::numeric_limits<std::uint16_t>::max())
			throw std::runtime_error("infinite loop has occured");

		const SoundGene
			*first_parent = nullptr, 
			*second_parent = nullptr;

		const std::size_t p0 = util::random<size_t>(0, elite - 1);
		std::size_t p1 = 0;

		std::size_t exit = 0; // exit for fail-safe
		while (++exit < std::numeric_limits<std::uint8_t>::max())
		{
			p1 = util::random<size_t>(0, elite - 1); // two random parents from the elite

			if (p0 == p1)
				continue;

			first_parent = &_population[p0];
			second_parent = &_population[p1];

			if (similiarity(*first_parent, *second_parent) > 0.1)
				continue;

			break;
		}

		if (p0 == p1 || first_parent == nullptr || second_parent == nullptr) // sanity checks
			continue;

		SoundGene child0(*first_parent); // deep copy
		SoundGene child1(*second_parent);

		const std::size_t gene_length = std::max<size_t>(child0.size(), child1.size());

		// K-POINT ALT 1
		//
		if (gene_length != 0)
		{
			child0.resize(gene_length); // resize to keep same length and allow for swap range
			child1.resize(gene_length);

			std::vector<size_t> n_points(util::random<size_t>(1, N_POINTS) * 2);

			for (size_t j = 0; j < n_points.size(); j += 2)
			{
				n_points[j] = util::random<size_t>(0, gene_length - 1);
				n_points[j + 1] = util::random<size_t>(0, gene_length - 1) + 1;
			}

			std::sort(n_points.begin(), n_points.end()); // sort in ascending order

			for (size_t j = 0; j < n_points.size(); j += 2)
			{
				size_t c0 = n_points[j];
				size_t c1 = n_points[j + 1];

				std::swap_ranges(	
					child0.begin() + c0,
					child0.begin() + c1,
					child1.begin() + c0);
			}

			child0.shrink();
			child1.shrink();
		}

		_proxy.emplace_back(_population.emplace_back(std::move(child0))); // add new children to the population
		_proxy.emplace_back(_population.emplace_back(std::move(child1)));

		// SINGLE POINT ALT 2 
		//
		//size_t point_0 = util::random<size_t>(1, child0.size() - 1);
		//size_t point_1 = util::random<size_t>(1, child1.size() - 1);

		//std::vector<std::shared_ptr<Command>> t0(child0.begin() + point_0, child0.end());
		//std::vector<std::shared_ptr<Command>> t1(child1.begin() + point_1, child1.end());

		//child0.resize(point_0);
		//child1.resize(point_1);

		//child0.insert(child0.end(), t1.begin(), t1.end());
		//child1.insert(child1.end(), t0.begin(), t0.end());

		// UNIFORM ALT 3
		// 
		//for (size_t i = 0; i < gene_length; ++i)
		//{
		//	if (util::random() > 0.5)
		//		std::iter_swap(child1.begin() + i, child2.begin() + i);
		//}
	}
}

void Evolution::mutation()
{
	std::for_each(std::execution::par_unseq,
		_population.begin() + (POPULATION_SIZE - _offspring_size), _population.end(),
		[this](SoundGene& gene)
		{
			if (util::random() > _mutation_rate || gene.size() <= 1)
				return;

			const int size = (int)std::ceil(gene.size() / (1.0 / _mutation_size));
			const int length = util::random(1, size); // determine number of points to mutate

			std::vector<int> rnd_points = util::random_vec<int>(gene.size() - 1, 1);
			const std::size_t min = std::min<std::size_t>(rnd_points.size(), length);

			for (int i = 0; i < min; ++i)
			{
				const std::size_t mp = rnd_points[i];

				if (util::random() <= REMOVE_MUTATION)
					gene.set(mp, nullptr);

				if (util::random() <= ADD_MUTATION)
					gene.insert(mp, Poke(util::ropoke(), util::rvpoke()));

				if (!gene.exists(mp))
					continue;

				if (util::random() <= COMMAND_MUTATION)
					gene.flip(mp);

				Command& command = gene.get(mp);
				CommandType type = command.get_type();

				switch (type)
				{
				case CT_Poke:
					{
						Poke* poke = static_cast<Poke*>(&command);

						if (util::random() <= OFFSET_MUTATION)
							poke->set_offset(util::ropoke());

						int change = util::random_arg<int>(-5, -4, -3, -2, -1, 1, 2, 3, 4, 5);
						std::uint32_t abs = static_cast<std::uint32_t>(std::abs(change));

						poke->add_value((poke->get_value() > abs) ? change : abs);
					}
					break;
				case CT_Sample:
					{
						Sample* sample = static_cast<Sample*>(&command);

						int change = util::random_arg<int>(-50, -25, 25, 50);
						std::size_t abs = static_cast<std::size_t>(std::abs(change));

						sample->add_size((sample->get_size() > abs) ? change : abs);
					}
					break;
				}
			}

			gene.shrink();
		});
}

double Evolution::similiarity(const SoundGene& lhs, const SoundGene& rhs)
{
	double result = 0.0;

	const auto lhs_range = lhs.range();
	const auto rhs_range = rhs.range();

	if (lhs_range.size() == 0 && rhs_range.size() == 0)
		return 1.0;
	if (lhs_range.size() == 0 || rhs_range.size() == 0)
		return 0.0;

	// TODO: FIX 24 OFFSET MATCHING EVERYTHING, POSSIBLE FIX: NEGATIVE SCORE WHEN WRONG

	std::array<bool, 25> lhs_offsets;
	for (size_t si = 0; si < std::min<size_t>(lhs_range.size(), rhs_range.size()); ++si) // do in reverse since only the last specified value matters
	{
		memset(lhs_offsets.data(), false, lhs_offsets.size());
		for (int j = std::get<1>(lhs_range[si]) - 1; j >= std::get<0>(lhs_range[si]); --j)
		{
			const Poke& lhs_poke = lhs.get<Poke>(j);
			if (!lhs_offsets[lhs_poke.get_offset()])
			{
				lhs_offsets[lhs_poke.get_offset()] = true;
				for (int k = std::get<1>(rhs_range[si]) - 1; k >= std::get<0>(rhs_range[si]); --k)
				{
					const Poke& rhs_poke = rhs.get<Poke>(k);
					if (lhs_poke.get_offset() == rhs_poke.get_offset())
					{
						const double val_diff = std::abs((int)lhs_poke.get_value() - (int)rhs_poke.get_value());
						const double val_ratio = 1.0 / (0.33 * val_diff + 1.0);

						result += val_ratio;

						break;
					}
				}
			}
		}

		const Sample& lhs_sample = lhs.get<Sample>(std::get<1>(lhs_range[si]));
		const Sample& rhs_sample = rhs.get<Sample>(std::get<1>(rhs_range[si]));

		const double smpl_diff = std::abs((int)lhs_sample.get_size() - (int)rhs_sample.get_size());
		const double smpl_ratio = 1.0 / (0.01 * smpl_diff + 1.0);

		result += smpl_ratio;
	}

	const std::size_t size = std::max<size_t>(lhs.size(), rhs.size());

	return (result / size);
}

void Evolution::reset()
{
	_population.clear();
	_old_population.clear();

	_models = std::vector<SoundGene>(MODEL_SAMPLES); // clear

	const auto random = util::random_vec<std::size_t>(std::size(examples));

	Interpreter interpreter;
	for (int i = 0; i < MODEL_SAMPLES; ++i)
		interpreter.read_str(&_models[i], examples[random[i]]);
}

bool Evolution::retry()
{
	if (_old_population.size() == 0)
		return false;

	_population = std::move(_old_population);
	_models.clear();

	return true;
}

std::vector<const SoundGene*> Evolution::output(size_t size,std::size_t step) const
{
	std::vector<const SoundGene*> genes;
	genes.reserve(size);

	for (size_t i = 0; i < size; ++i)
	{
		if ((step + i) < 0 || (step + i) >= _population.size())
			return std::vector<const SoundGene*>();

		genes.push_back(&_population[step + i]);
	}

	return genes;
}

bool Evolution::save(const std::string& filename) const
{
	if (filename.empty())
		return false;

	std::ofstream out;
	out.open(filename, std::ofstream::trunc);

	out << "// DO NOT REMOVE OR ADD ANY 'RUN' COMMANDS\n";
	for (size_t i = 0; i < _population.size(); ++i)
	{
		for (size_t j = 0; j < _population[i].size(); ++j)
			out << _population[i].get(j).print() + '\n';

		out << "RUN\n";
	}

	out.close();

	return true;
}
int Evolution::load(const std::string& filename)
{
	std::vector<SoundGene> genes = Interpreter().read_file<SoundGene>(filename);

	if (genes.size() == 0)
		return -1;

	if (genes.size() <= ROWS * COLUMNS)
	{
		_models = std::move(genes);

		if (!_models.empty())
			return 0;
	}
	else if (genes.size() >= USABLE_POPULATION)
	{
		_population = std::move(genes);

		if (!_population.empty())
			return 1;
	}

	return -1;
}