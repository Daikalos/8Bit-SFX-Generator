#define NATIVE_CODE
#include "Evolution.h"

using namespace IESFX;

Evolution::Evolution(double mutation_rate, double mutation_size)
	: _mutation_rate(mutation_rate), _mutation_size(mutation_size), _models(std::vector<SoundGene>(MODEL_SAMPLES))
{
	std::vector<size_t> random = util::random(util::arr_size(examples));

	Interpreter interpreter;
	for (int i = 0; i < MODEL_SAMPLES; ++i)
		interpreter.read_str(&_models[i], examples[random[i]]);
}

void Evolution::add_model(SoundGene& gene)
{
	_models.push_back(gene);
}

void Evolution::remove_model(const SoundGene& gene)
{
	_models.erase(std::remove_if(
		std::execution::par_unseq, 
		_models.begin(), _models.end(), 
		[&gene](const SoundGene& model)
		{
			return gene == model;
		}), _models.end());
}

int Evolution::execute(size_t max_generations, double max_quality)
{
	if (_models.size() == 0)
		return -1;

	_active = true;

	_old_population = _population;

	_max_generations = max_generations;
	_max_quality = max_quality;

	_generations = 0;
	_quality = 0;

	initialize();

	while (!complete())
	{
		std::for_each(
			std::execution::par_unseq,
			_population.begin(),
			_population.end(),
			[&](SoundGene& candidate) // evaluate each candidate
			{
				evaluate(candidate);
			});

		selection();

		crossover();

		mutation();

		double sum = 0.0;
		std::for_each(
			std::execution::par_unseq, 
			_population.begin(), 
			_population.begin() + AVERAGE_SAMPLE,
			[&sum](const SoundGene& gene)
			{ 
				sum += gene._fitness;
			});

		_quality = sum / (double)AVERAGE_SAMPLE;
		++_generations;
	}

	// sort before finished
	//
	std::sort(std::execution::par_unseq,
		_population.begin(), _population.end());

	_models.clear();

	_generations = 0;
	_quality = 0;

	_active = false;

	return 0;
}

void Evolution::initialize()
{
	_population = std::vector<SoundGene>(POPULATION_SIZE);
	_population.resize(POPULATION_SIZE - _models.size());

	std::for_each(
		std::execution::par_unseq,
		_population.begin(), _population.end(),
		[](SoundGene& gene)
		{
			gene.push({ 24, 14 }); // always volume on

			std::vector<RESID::reg8> offsets(util::random<RESID::reg8>(24));

			for (int s = util::random(1, 7); s > 0; --s)
			{
				for (int p = util::ropoke(); p > 0; --p)
				{
					gene.push({ offsets[p], util::rvpoke() });
				}
				gene.push({ util::rsample() });
				offsets = util::random<RESID::reg8>(24);
			}
		});

	for (size_t i = 0; i < _models.size(); ++i)
		_population.push_back(_models[i]);
}

void Evolution::evaluate(SoundGene& candidate)
{
	candidate._fitness = 0;

	const double simi_mul = 2.75;
	const double smpl_mul = 0.25;
	const double time_mul = 0.15;

	// adjust fitness based on similiarity	TODO: FIX BIAS TOWARDS CERTAIN MODELS, EVERYONE HAS SIMILIARITY TO THE FIRST SEGMENT
	// 

	std::vector<std::tuple<int, int, int>> c_range = candidate.range<int>();

	if (c_range.size() == 0)
		return;

	std::for_each(
		std::execution::par_unseq,
		_models.begin(), _models.end(),
		[&](const SoundGene& model)
		{
			std::vector<std::tuple<int, int, int>> m_range = model.range<int>();

			double score = 0.0;
			for (int si = 0; si < std::min<int>(c_range.size(), m_range.size()); ++si) // do in reverse since only the last specified value matters
			{
				std::vector<bool> m_offsets(25, false);
				for (int j = std::get<1>(m_range[si]) - 1; j >= std::get<0>(m_range[si]); --j)
				{
					Poke* m_poke = static_cast<Poke*>(model.get(j));
					if (!m_offsets[m_poke->offset])
					{
						m_offsets[m_poke->offset] = true;
						for (int k = std::get<1>(c_range[si]) - 1; k >= std::get<0>(c_range[si]); --k)
						{
							Poke* c_poke = static_cast<Poke*>(candidate.get(k));
							if (m_poke->offset == c_poke->offset)
							{
								double val_diff = std::abs((int)m_poke->value - (int)c_poke->value);
								double val_ratio = 1.0 / (0.33 * val_diff + 1.0);

								score += val_ratio;

								break;
							}
						}
					}
				}

				Sample* lhs_sample = static_cast<Sample*>(model.get(std::get<1>(m_range[si])));
				Sample* rhs_sample = static_cast<Sample*>(candidate.get(std::get<1>(c_range[si])));

				double smpl_diff = std::abs((int)lhs_sample->size - (int)rhs_sample->size);
				double smpl_ratio = 1.0 / (0.01 * smpl_diff + 1.0);

				score += smpl_ratio;
			}

			double similarity = (score / model.size()); // not really the correct way, but yields better output???
			candidate._fitness += (similarity > 0.6 ? 0.6 / (similarity + 0.4) : similarity) * simi_mul;
		});

	// adjust fitness based on samples
	//
	int poke_count = 0;
	double time = 0.0;
	for (size_t i = 0; i < candidate.size(); ++i)
	{
		Poke* poke = dynamic_cast<Poke*>(candidate.get(i));
		Sample* sample = dynamic_cast<Sample*>(candidate.get(i));

		if (sample != nullptr)
		{
			time += (double)util::time(sample->size);

			if (poke_count == 0)
				candidate._fitness += -smpl_mul; // no pokes given before sample is bad

			poke_count = 0;
		}
		else if (poke != nullptr)
			++poke_count;
	}

	if (poke_count > 0)
		candidate._fitness += -poke_count * smpl_mul; // pokes but no sample given is bad

	// adjust fitness based on length of audio
	//
	if (time <= DBL_EPSILON)
		candidate._fitness = -DBL_MAX; // length of zero means no audio, extremely bad candidate
	else if (time < 0.2)
		candidate._fitness += -(0.2 / time) * time_mul;
	else if (time > 1.4)
		candidate._fitness += -(time / 1.4) * time_mul;
}

void Evolution::selection()
{
	// sort in descending order by fitness value to allow a rank based selection
	//
	std::sort(std::execution::par_unseq, 
		_population.begin(), _population.end());

	std::for_each(std::execution::par_unseq,
		_population.begin(), _population.end(),
		[&](SoundGene& gene)
		{
			size_t i = &gene - _population.data();

			double chance = (i + 1) / (double)POPULATION_SIZE;

			if (util::random() + 0.3 <= chance) // +0.2 to give better chance for lower fitness to survive
				gene._dead = true;
		});

	_population.erase(std::remove_if(
		std::execution::par_unseq,
		_population.begin(), _population.end(),
		[&](const SoundGene& gene)
		{
			return gene._dead && _population.size() > 2;
		}), _population.end());

	if (_population.size() % 2 != 0) // remove worst lone parent to keep things even for creating offspring
		_population.pop_back();
}

void Evolution::crossover()
{
	size_t elite = _population.size();
	_offspring_size = POPULATION_SIZE - elite;

	while (_population.size() != POPULATION_SIZE)
	{
		size_t p0 = 0, p1 = 0, exit = 0; // exit for fail-safe

		p0 = util::random<size_t>(0, elite - 1);
		do p1 = util::random<size_t>(0, elite - 1);
		while (p0 == p1 || (similiarity(_population[p0], _population[p1]) > 0.1 && ++exit < 128)); // two random parents from the elite

		SoundGene child0(_population[p0]); // deep copy
		SoundGene child1(_population[p1]);

		size_t gene_length = std::max<size_t>(_population[p0].size(), _population[p1].size());

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

			std::sort(std::execution::par_unseq, // sort in ascending order
				n_points.begin(), n_points.end());

			for (size_t j = 0; j < n_points.size(); j += 2)
			{
				size_t c0 = n_points[j];
				size_t c1 = n_points[j + 1];

				std::swap_ranges(std::execution::par_unseq,
					child0.begin() + c0,
					child0.begin() + c1,
					child1.begin() + c0);
			}

			child0.shrink();
			child1.shrink();
		}

		evaluate(_population.emplace_back(std::move(child0))); // add new children to the population
		evaluate(_population.emplace_back(std::move(child1)));

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
		_population.begin() + (POPULATION_SIZE - _offspring_size),
		_population.end(),
		[&](SoundGene& gene) 
		{
			if (util::random() > _mutation_rate)
				return;

			int size = static_cast<int>(std::ceil(gene.size() / (1.0 / _mutation_size)));
			int length = util::random(0, size - 1);

			for (int j = 0; j < length; ++j)
			{
				size_t mp = (gene.size() > 1) ? util::random<size_t>(1, gene.size() - 1) : 0;

				if (util::random() <= COMMAND_MUTATION)
					gene.flip(mp);

				if (util::random() <= REMOVE_MUTATION)
					gene.set(mp, nullptr);

				if (util::random() <= ADD_MUTATION)
					gene.insert(mp, { util::ropoke(), util::rvpoke() });

				Poke* poke = dynamic_cast<Poke*>(gene.get(mp));
				Sample* sample = dynamic_cast<Sample*>(gene.get(mp));

				if (poke != nullptr)
				{
					if (util::random() <= OFFSET_MUTATION)
						poke->offset = util::ropoke();

					int change = util::random_arg<int>(-5, -4, -3, -2, -1, 1, 2, 3, 4, 5);
					uint32_t abs = static_cast<uint32_t>(std::abs(change));

					poke->value += (poke->value > abs) ? change : abs;
				}
				else if (sample != nullptr)
				{
					int change = util::random_arg<int>(-50, -25, 25, 50);
					size_t abs = static_cast<size_t>(std::abs(change));

					sample->size += (sample->size > abs) ? change : abs;
				}
			}

			gene.shrink();
		});
}

bool Evolution::complete()
{
	return (_generations >= _max_generations || _quality >= _max_quality);
}

double Evolution::similiarity(const SoundGene& lhs, const SoundGene& rhs)
{
	double result = 0.0;

	std::vector<std::tuple<int, int, int>> lhs_range = lhs.range<int>();
	std::vector<std::tuple<int, int, int>> rhs_range = rhs.range<int>();

	if (lhs_range.size() == 0 && rhs_range.size() == 0)
		return 1.0;
	if (lhs_range.size() == 0 || rhs_range.size() == 0)
		return 0.0;

	// TODO: FIX 24 OFFSET MATCHING EVERYTHING, POSSIBLE FIX: NEGATIVE SCORE WHEN WRONG

	for (size_t si = 0; si < std::min<size_t>(lhs_range.size(), rhs_range.size()); ++si) // do in reverse since only the last specified value matters
	{
		std::vector<bool> lhs_offsets(25, false);
		for (int j = std::get<1>(lhs_range[si]) - 1; j >= std::get<0>(lhs_range[si]); --j)
		{
			Poke* lhs_poke = static_cast<Poke*>(lhs.get(j));
			if (!lhs_offsets[lhs_poke->offset])
			{
				lhs_offsets[lhs_poke->offset] = true;
				for (int k = std::get<1>(rhs_range[si]) - 1; k >= std::get<0>(rhs_range[si]); --k)
				{
					Poke* rhs_poke = static_cast<Poke*>(rhs.get(k));
					if (lhs_poke->offset == rhs_poke->offset)
					{
						double pk_diff = std::abs((int)lhs_poke->value - (int)rhs_poke->value);
						double pk_ratio = 1.0 / (pk_diff + 1.0);

						result += pk_ratio;

						break;
					}
				}
			}
		}

		Sample* lhs_sample = static_cast<Sample*>(lhs.get(std::get<1>(lhs_range[si])));
		Sample* rhs_sample = static_cast<Sample*>(rhs.get(std::get<1>(rhs_range[si])));

		double smpl_diff = std::abs((int)lhs_sample->size - (int)rhs_sample->size);
		double smpl_ratio = 1.0 / (smpl_diff + 1.0);

		result += smpl_ratio;
	}

	size_t size = std::max<size_t>(lhs.size(), rhs.size());

	return (result / size);
}

void Evolution::reset()
{
	_population.clear();
	_old_population.clear();

	_models = std::vector<SoundGene>(MODEL_SAMPLES); // clear

	std::vector<size_t> random = util::random(util::arr_size(examples));

	Interpreter interpreter;
	for (int i = 0; i < MODEL_SAMPLES; ++i)
		interpreter.read_str(&_models[i], examples[random[i]]);
}

bool Evolution::retry()
{
	if (_old_population.size() == 0)
		return false;

	_population = _old_population;

	_old_population.clear();
	_models.clear();

	return true;
}

std::vector<SoundGene> Evolution::output(size_t size, size_t step)
{
	std::vector<SoundGene> genes;
	genes.reserve(size);

	for (size_t i = 0; i < size; ++i)
	{
		if ((step + i) < 0 || (step + i) >= _population.size())
			return std::vector<SoundGene>();

		genes.push_back(_population[step + i]);
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
			out << _population[i].get(j)->print() + '\n';

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

	if (genes.size() <= 12)
	{
		_models = std::move(genes);

		if (_models.size() != 0)
			return 0;
	}
	else if (genes.size() >= USABLE_POPULATION)
	{
		_population = std::move(genes);

		if (_population.size() != 0)
			return 1;
	}

	return -1;
}