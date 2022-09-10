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
	: _offset(o), _value(v) {}

const std::string& Poke::print() const
{
	if (_update_print)
	{
		_print = std::string("poke " +
			std::to_string(_offset) + " " +
			std::to_string(_value));

		_update_print = false;
	}

	return _print;
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
	if (rhs->get_type() != CT_Poke)
		return false;

	const Poke* poke = static_cast<const Poke*>(rhs);

	return _offset == poke->_offset && _value == poke->_value;
}
CommandType Poke::get_type() const noexcept
{
	return CT_Poke;
}

RESID::reg8 Poke::get_offset() const noexcept
{
	return _offset;
}
RESID::reg8 Poke::get_value() const noexcept
{
	return _value;
}

void Poke::set_offset(const RESID::reg8 offset)
{
	_offset = offset;
	_update_print = true;
}
void Poke::set_value(const RESID::reg8 value)
{
	_value = value;
	_update_print = true;
}

void Poke::add_value(const RESID::reg8 value)
{
	set_value(_value + value);
}

//////////////////////////////

Sample::Sample(std::size_t s) 
	: _size(s) {}

const std::string& Sample::print() const
{
	if (_update_print)
	{
		_print = std::string("sample " + 
			std::to_string(_size));

		_update_print = false;
	}

	return _print;
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
	if (rhs->get_type() != CT_Sample)
		return false;

	const Sample* sample = static_cast<const Sample*>(rhs);

	return _size == sample->_size;
}

CommandType Sample::get_type() const noexcept
{
	return CT_Sample;
}

RESID::reg8 Sample::get_size() const noexcept
{
	return _size;
}

void Sample::set_size(const std::size_t size)
{
	_size = size;
	_update_print = true;
}
void Sample::add_size(const std::size_t size)
{
	set_size(_size + size);
}
