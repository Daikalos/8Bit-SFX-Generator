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
		[](const std::unique_ptr<Command>& command)
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
