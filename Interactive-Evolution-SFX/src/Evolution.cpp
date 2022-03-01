#include "Evolution.h"

using namespace IESFX;

Evolution::Evolution()
	: _mutation_rate(0.02), _mutation_size(0.02)
{
	_population.resize(POPULATION_SIZE);
}

Evolution::~Evolution()
{

}

void Evolution::reset()
{

}

void Evolution::execute()
{

}

std::vector<SoundGene>* Evolution::output(size_t size, size_t step)
{

	return nullptr;
}
