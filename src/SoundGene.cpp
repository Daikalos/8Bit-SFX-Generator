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

std::size_t SoundGene::size() const
{
	return _gene.size();
}

void SoundGene::resize(const size_t size)
{
	_gene.resize(size);
}
void SoundGene::shrink()
{
	_gene.erase(std::remove_if(_gene.begin(), _gene.end(),
		[](const std::unique_ptr<Command>& command)
		{
			return command.get() == nullptr;
		}), _gene.end());
}

std::string SoundGene::print() const
{
	std::string output;
	output.reserve(_gene.size() * 13); // 13 for an average size of each line

	for (const auto& s : _gene)
		output += s->print() + '\n';

	return output;
}

SoundGene& SoundGene::operator=(const SoundGene& rhs)
{
	_fitness = rhs._fitness;
	_dead = rhs._dead;

	std::vector<std::unique_ptr<Command>> new_gene;

	new_gene.reserve(rhs.size());
	for (size_t i = 0; i < rhs.size(); ++i)
		new_gene.push_back(rhs.get(i)->clone());

	_gene = std::move(new_gene);

	return *this;
}

const Command* SoundGene::get(const size_t index) const
{ 
	return _gene[index].get();
}
Command* SoundGene::get(const size_t index)
{ 
	return _gene[index].get(); 
}

void SoundGene::push(const Poke& poke)
{ 
	_gene.push_back(poke.clone()); 
}
void SoundGene::push(const Sample& sample)
{ 
	_gene.push_back(sample.clone()); 
}

void SoundGene::set(const size_t index, std::nullptr_t)
{
	_gene[index].reset();
}
void SoundGene::set(const size_t index, const unsigned int offset, const unsigned int value)
{
	Command* command = _gene[index].get();

	if (command->get_type() == CT_Poke)
	{
		Poke* poke = static_cast<Poke*>(command);

		poke->set_offset(offset);
		poke->set_value(value);
	}
}
void SoundGene::set(const size_t index, const size_t size)
{
	Command* command = _gene[index].get();

	if (command->get_type() == CT_Sample)
		static_cast<Sample*>(command)->set_size(size);
}
void SoundGene::set(const size_t index, const Command* cmd)
{
	Command* command = _gene[index].get();

	if (command->get_type() == cmd->get_type())
		*command = *cmd;
}

void SoundGene::insert(const size_t pos, const Command* command)
{
	_gene.insert(_gene.begin() + pos, command->clone());
}

void SoundGene::flip(const size_t index)
{
	const Command* command = get(index);

	if (command)
		_gene[index] = std::move(command->flip());
}

bool SoundGene::operator<(const SoundGene& rhs) const
{
	return _fitness > rhs._fitness;
}
bool SoundGene::operator==(const SoundGene& rhs) const
{
	if (size() != rhs.size())
		return false;

	for (size_t i = 0; i < rhs.size(); ++i)
	{
		if (*get(i) != rhs.get(i))
			return false;
	}

	return true;
}

std::vector<std::tuple<int, int, int>> SoundGene::range() const
{
	std::vector<std::tuple<int, int, int>> result;
	for (std::size_t i = 0, index = 0; i < size(); ++i)
	{
		if (get(i)->get_type() == CT_Sample)
		{
			result.push_back(std::make_tuple(index, i, i - index));
			index = i + 1;
		}
	}
	return result;
}

void SoundGene::read_poke(unsigned int offset, unsigned int value)
{
	push({ offset, value });
}
void SoundGene::read_sample(size_t size)
{
	push({ size });
}
