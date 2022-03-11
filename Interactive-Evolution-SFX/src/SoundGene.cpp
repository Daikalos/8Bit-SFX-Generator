#define NATIVE_CODE
#include "SoundGene.h"

using namespace IESFX;

SoundGene::SoundGene(const SoundGene& rhs)
	: _fitness(rhs._fitness), _dead(rhs._dead)
{
	_gene.reserve(rhs.size());
	for (size_t i = 0; i < rhs.size(); ++i)
		_gene.push_back(rhs.get(i)->clone());
}

void SoundGene::resize(const size_t size)
{
	_gene.resize(size);
}
void SoundGene::shrink()
{
	_gene.erase(std::remove_if(
		std::execution::par_unseq,
		_gene.begin(), _gene.end(),
		[](std::shared_ptr<Command>& command)
		{
			return command.get() == nullptr;
		}), _gene.end());
}

std::string SoundGene::output() const
{
	std::string output;

	for (const auto& s : _gene)
		output += s->print() + '\n';

	return output;
}

SoundGene& SoundGene::operator=(const SoundGene& rhs)
{
	_fitness = rhs._fitness;
	_dead = rhs._dead;

	_gene.clear();

	_gene.reserve(rhs.size());
	for (size_t i = 0; i < rhs.size(); ++i)
		_gene.push_back(rhs.get(i)->clone());

	return *this;
}
