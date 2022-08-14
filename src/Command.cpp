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
#include "Command.h"

using namespace IESFX;

Poke::Poke(RESID::reg8 o, RESID::reg8 v)
	: offset(o), value(v) { }

std::string Poke::print() const
{
	return std::string("poke " +
		std::to_string(offset) + " " +
		std::to_string(value));
}
std::unique_ptr<Command> Poke::clone() const
{
	return std::make_unique<Poke>(*this);
}
std::unique_ptr<Command> Poke::flip() const
{
	return std::make_unique<Sample>(Sample(util::rsample()));
}
bool Poke::equal_to(const Command* rhs) const
{
	const Poke* poke = dynamic_cast<const Poke*>(rhs);

	if (poke == nullptr)
		return false;

	return this->offset == poke->offset && this->value == poke->value;
}

Sample::Sample(size_t s)
	: size(s) { }

std::string Sample::print() const
{
	return std::string("sample " + std::to_string(size));
}
std::unique_ptr<Command> Sample::clone() const
{
	return std::make_unique<Sample>(*this);
}
std::unique_ptr<Command> Sample::flip() const
{
	return std::make_unique<Poke>(Poke(util::ropoke(), util::rvpoke()));
}
bool Sample::equal_to(const Command* rhs) const
{
	const Sample* sample = dynamic_cast<const Sample*>(rhs);

	if (sample == nullptr)
		return false;

	return this->size == sample->size;
}
