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

#pragma once

#include <resid/siddefs.h>
#include <string>
#include <memory>

#include "Utilities.h"

namespace IESFX
{
	enum CommandType : short
	{
		CT_None = -1,

		CT_Poke,
		CT_Sample,

		CT_Count
	};

	struct Command
	{
		Command() = default;
		virtual ~Command() = default;

		[[nodiscard]] virtual std::string print() const = 0;
		[[nodiscard]] virtual std::unique_ptr<Command> clone() const = 0;
		[[nodiscard]] virtual std::unique_ptr<Command> flip() const = 0;

		[[nodiscard]] virtual bool equal_to(const Command* rhs) const = 0;

		[[nodiscard]] virtual CommandType get_type() const noexcept { return CT_None; }

		[[nodiscard]] bool operator==(const Command* rhs) const { return equal_to(rhs); }
		[[nodiscard]] bool operator!=(const Command* rhs) const { return !equal_to(rhs); }
	};

	struct Poke : public Command
	{
		Poke(RESID::reg8 o, RESID::reg8 v);

		[[nodiscard]] std::string print() const override;
		[[nodiscard]] std::unique_ptr<Command> clone() const override;
		[[nodiscard]] std::unique_ptr<Command> flip() const override;

		[[nodiscard]] bool equal_to(const Command* rhs) const override;

		[[nodiscard]] virtual CommandType get_type() const noexcept override;

		RESID::reg8 offset{0}, value{0};
	};

	struct Sample : public Command
	{
		Sample(std::size_t s);

		[[nodiscard]] std::string print() const override;
		[[nodiscard]] std::unique_ptr<Command> clone() const override;
		[[nodiscard]] std::unique_ptr<Command> flip() const override;

		[[nodiscard]] bool equal_to(const Command* rhs) const override;

		[[nodiscard]] virtual CommandType get_type() const noexcept override;

		std::size_t size{0};
	};
}

