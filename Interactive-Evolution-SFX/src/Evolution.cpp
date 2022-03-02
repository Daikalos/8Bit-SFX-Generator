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

void Evolution::reset()
{
	_population.clear();
	initialize();
}

int Evolution::execute()
{
	if (_models.size() == 0)
		return -1;



	return 0;
}

std::vector<SoundGene> Evolution::output(size_t size, size_t step)
{
	std::vector<SoundGene> genes;
	genes.reserve(size);

	for (size_t i = 0; i < size; ++i)
	{
		if ((step + i) >= _population.size())
			return std::vector<SoundGene>();

		genes.push_back(_population[step + i].first);
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
	for (int i = _population.size() - 1; i >= 0; --i)
	{
		for (int j = _population[i].first.size() - 1; j >= 0; --j)
		{
			out << _population[i].first.get(j)->print() + '\n';
		}
		out << "RUN\n";
	}

	out.close();

	return true;
}
bool Evolution::load(const std::vector<SoundGene>& genes)
{
	if (genes.size() != _population.size())
		return false;

	for (size_t i = 0; i < _population.size(); ++i)
		_population[i].first = genes[i];

	return true;
}

void Evolution::initialize()
{
	_population.resize(POPULATION_SIZE);

	for (int i = _population.size() - 1; i >= 0; --i)
	{
		_population[i].first.push({ 24, 15 }); // always volume on

		size_t commands = util::random(0, 128);
		for (size_t j = 0; j < commands; ++j)
		{
			if (util::random(0.0, 1.0) > 0.1)
				_population[i].first.push({
					util::random<RESID::reg8>(0, 23),
					util::random<RESID::reg8>(0, 100) });
			else
				_population[i].first.push({ util::random<size_t>(0, 1000) });
		}
	}
}
