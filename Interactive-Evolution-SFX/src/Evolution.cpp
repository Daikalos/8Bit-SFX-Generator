#define NATIVE_CODE
#include "Evolution.h"

using namespace IESFX;

Evolution::Evolution(double mutation_rate, double mutation_size)
	: _mutation_rate(mutation_rate), _mutation_size(mutation_size)
{
	initialize();
}

Evolution::~Evolution()
{

}

int Evolution::execute(size_t max_generations, double max_quality)
{
	if (_models.size() == 0)
		return -1;

	_max_generations = max_generations;
	_max_quality = max_quality;

	size_t generations = 0;
	double quality = 0;

	while (!complete(generations, quality))
	{
		shuffle();

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

		quality = _population.front()._fitness;
		++generations;
	}

	// sort before finished
	//
	std::sort(
		std::execution::par_unseq,
		_population.begin(),
		_population.end(),
		[&](const SoundGene& g1, const SoundGene& g2)
		{
			return g1._fitness > g2._fitness;
		});

	return 0;
}

void Evolution::initialize()
{
	Interpreter interpreter;
	for (int i = 0; i < util::arr_size(examples); ++i)
		interpreter.read_str(_models.emplace_back(new SoundGene()), examples[i]);

	_population.resize(POPULATION_SIZE);
	for (int i = 0; i < POPULATION_SIZE; ++i)
	{
		_population[i].push({ 24, 14 }); // always volume on

		std::vector<RESID::reg8> offsets = util::random<RESID::reg8>(24);

		for (size_t j = 0, index = 0, size = util::random(0, 128); j < size; ++j)
		{
			if (util::random() > 0.125 && index < offsets.size())
				_population[i].push({ offsets[index++], util::rvpoke() });
			else
			{
				_population[i].push({ util::rsample() });

				offsets = util::random<RESID::reg8>(24);
				index = 0;
			}
		}
	}

	execute();

	for (int i = 0; i < _models.size(); ++i)
		delete _models[i];

	_models.clear();
}

void Evolution::shuffle()
{
	std::shuffle(_population.begin(), _population.end(), util::dre);
}

void Evolution::evaluate(SoundGene& candidate)
{
	const double time_mul = 5.0;
	const double simi_mul = 2.0;

	double time = 0.0;
	for (size_t i = 0; i < candidate.size(); ++i)
	{
		Poke* poke = dynamic_cast<Poke*>(candidate.get(i));
		Sample* sample = dynamic_cast<Sample*>(candidate.get(i));

		if (poke != nullptr)
		{
			for (size_t j = 0; j < _models.size(); ++j)
			{
				SoundGene* gene = _models[j];
				for (size_t k = i; k < gene->size(); ++k)
				{
					Poke* m_poke = dynamic_cast<Poke*>(gene->get(k));
					Sample* m_sample = dynamic_cast<Sample*>(gene->get(k));

					if (m_sample != nullptr)
						break;

					if (m_poke->offset == poke->offset)
					{
						int difference = std::abs((int)m_poke->value - (int)poke->value);

						if (difference == 0) // exact similiarity is not supported
							candidate._fitness += -1.0;
						else
							candidate._fitness += (1.0 / (double)difference) * simi_mul;
					}
				}
			}
		}
		else if (sample != nullptr)
			time += (double)util::time(sample->size);
	}

	// adjust fitness based on length of audio
	//
	if (time == 0.0)
		candidate._fitness = 0.0;
	else if (time < 0.3)
		candidate._fitness -= (0.3 / time) * time_mul;
	else if (time > 1.5)
		candidate._fitness -= (time / 1.5) * time_mul;
	else
		candidate._fitness += time_mul;
}

void Evolution::selection()
{
	// sort in descending order by fitness value to allow a rank based selection
	//
	std::sort(
		std::execution::par_unseq,
		_population.begin(),
		_population.end(),
		[&](const SoundGene& g1, const SoundGene& g2)
		{
			return g1._fitness > g2._fitness;
		});

	for (ptrdiff_t i = POPULATION_SIZE - 1; i >= 0; --i)
	{
		double chance = (i + 1) / (double)POPULATION_SIZE; // rank

		if (util::random() <= chance && _population.size() > 2) // ensure always two parents
			_population.erase(_population.begin() + i);
	}

	if (_population.size() % 2 != 0) // remove worst lone parent to keep things even for creating offspring
		_population.erase(_population.end() - 1);
}

void Evolution::crossover()
{
	size_t elite_size = _population.size();
	_offspring_size = POPULATION_SIZE - elite_size;

	for (int i = POPULATION_SIZE - 1; i >= elite_size; i -= 2)
	{
		size_t p0 = 0, p1 = 0;

		p0 = util::random<size_t>(0, elite_size - 1);
		do p1 = util::random<size_t>(0, elite_size - 1);
		while (p0 == p1); // two random parents from the elite

		SoundGene child1(_population[p0]);
		SoundGene child2(_population[p1]);

		size_t gene_length = std::max<size_t>(_population[p0].size(), _population[p1].size());

		if (gene_length == 0)
			continue;

		child1.resize(gene_length); // resize to keep same length and allow for swap range
		child2.resize(gene_length);

		size_t c0 = util::random<size_t>(0, gene_length - 1);
		size_t c1 = util::random<size_t>(0, gene_length - 1) + 1;

		if (c0 > c1)
			std::swap(c0, c1);

		std::swap_ranges(std::execution::par_unseq, 
			child1.begin() + c0, 
			child1.begin() + c1, 
			child2.begin() + c0);

		child1.shrink();
		child2.shrink();

		evaluate(_population.emplace_back(child1)); // add new children to the population
		evaluate(_population.emplace_back(child2));
	}
}

void Evolution::mutation()
{
	for (int i = _population.size() - 1; i >= (_population.size() - _offspring_size); --i)
	{
		if (util::random(0.0, 1.0) > _mutation_rate)
			continue;

		size_t gene_length;
		if (!(gene_length = _population[i].size()))
			continue;

		int size = std::ceil((double)gene_length / (1.0 / _mutation_size));
		int length = util::random(1, size);

		for (size_t j = 0; j < length; ++j)
		{
			size_t mp = util::random<size_t>(0, gene_length - 1);

			Poke* poke = dynamic_cast<Poke*>(_population[i].get(mp));
			Sample* sample = dynamic_cast<Sample*>(_population[i].get(mp));

			if (util::random() > COMMAND_MUTATION_CHANCE)
			{
				if (poke != nullptr)
				{
					if (util::random() > OFFSET_MUTATION_CHANCE)
						poke->offset = util::random(0, 23);
					else
						poke->value += (poke->value > 0) ? util::random(-1, 1) : 1;
				}
				else if (sample != nullptr)
					sample->size += (sample->size >= 5) ? util::random(-5, 5) : 5;
			}
			else
			{
				if (poke != nullptr)
					_population[i].set(mp, util::ropoke(), util::rvpoke());
				else if (sample != nullptr)
					_population[i].set(mp, util::rsample());
			}
		}
	}
}

bool Evolution::complete(int current_generation, double current_quality)
{
	return (current_generation >= _max_generations || current_quality >= _max_quality);
}

void Evolution::reset()
{
	_population.clear();
	_models.clear();

	initialize();
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
bool Evolution::load(const std::string& filename)
{
	std::vector<SoundGene> genes = Interpreter().read_file<SoundGene>(filename);

	if (genes.size() != _population.size())
		return false;

	_population = genes;

	return true;
}