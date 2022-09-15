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

	class Command
	{
	public:
		using Ptr = std::unique_ptr<Command>;

	public:
		Command() = default;
		virtual ~Command() = default;

		[[nodiscard]] virtual const std::string& print() const = 0;

		[[nodiscard]] virtual Ptr clone() const = 0;
		[[nodiscard]] virtual Ptr flip() const = 0;

		[[nodiscard]] virtual bool equal_to(const Command* rhs) const = 0;

		[[nodiscard]] virtual CommandType get_type() const noexcept { return CT_None; }

		[[nodiscard]] bool operator==(const Command* rhs) const { return equal_to(rhs); }
		[[nodiscard]] bool operator!=(const Command* rhs) const { return !equal_to(rhs); }

	protected:
		mutable std::string _print;
		mutable bool _update_print{true};
	};

	class Poke final : public Command
	{
	public:
		Poke(RESID::reg8 o, RESID::reg8 v);

		[[nodiscard]] const std::string& print() const override;

		[[nodiscard]] Ptr clone() const override;
		[[nodiscard]] Ptr flip() const override;

		[[nodiscard]] bool equal_to(const Command* rhs) const override;

		[[nodiscard]] CommandType get_type() const noexcept override;

		[[nodiscard]] RESID::reg8 get_offset() const noexcept;
		[[nodiscard]] RESID::reg8 get_value() const noexcept;

		void set_offset(const RESID::reg8 offset);
		void set_value(const RESID::reg8 value);

		void add_value(const RESID::reg8 value);

	private:
		RESID::reg8 _offset{0}, _value{0};
	};

	class Sample final : public Command
	{
	public:
		Sample(std::size_t s);

		[[nodiscard]] const std::string& print() const override;

		[[nodiscard]] Ptr clone() const override;
		[[nodiscard]] Ptr flip() const override;

		[[nodiscard]] bool equal_to(const Command* rhs) const override;

		[[nodiscard]] CommandType get_type() const noexcept override;

		[[nodiscard]] RESID::reg8 get_size() const noexcept;

		void set_size(const std::size_t size);
		void add_size(const std::size_t size);

	private:
		std::size_t _size{0};
	};
}

