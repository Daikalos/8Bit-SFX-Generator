#include "Evolution.h"

using namespace IESFX;

Evolution::Evolution()
{
	_population.resize(POPULATION_SIZE);
}

Evolution::~Evolution()
{
	delete _population;
}
