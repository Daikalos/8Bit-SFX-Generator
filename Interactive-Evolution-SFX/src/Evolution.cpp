#include "Evolution.h"

using namespace IESFX;

Evolution::Evolution()
	: _mutation_rate(0.02), _mutation_size(0.02)
{
	initialize();
}

Evolution::~Evolution()
{

}

int Evolution::execute()
{
	if (_models.size() == 0)
		return -1;

	int generations = 0;
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

	return 0;
}

void Evolution::initialize()
{
	_population.resize(POPULATION_SIZE);

	Interpreter interpreter;
	for (int i = _population.size() - 1; i >= 0; --i)
	{
		//interpreter.read_str(&_population[i], examples[0]);

		_population[i].push({ 24, 14 }); // always volume on

		size_t commands = util::random(0, 128);
		for (size_t j = 0; j < commands; ++j)
		{
			if (util::random(0.0, 1.0) > 0.1)
				_population[i].push({
					util::random<RESID::reg8>(0, 23),
					util::random<RESID::reg8>(0, 100) });
			else
				_population[i].push({ util::random<size_t>(0, 1000) });
		}
	}
}

void Evolution::shuffle()
{
	std::shuffle(_population.begin(), _population.end(), util::dre);
}

void Evolution::evaluate(SoundGene& candidate)
{

}

void Evolution::selection()
{

}

void Evolution::crossover()
{

}

void Evolution::mutation()
{

}

bool Evolution::complete(int generation, double quality)
{
	return (generation >= MAX_GENERATIONS || quality >= MAX_QUALITY);
}

void Evolution::reset()
{
	_population.clear();
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