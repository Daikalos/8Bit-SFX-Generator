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

#include <resid/sid.h>
#include <SFML/Config.hpp>
#include <vector>
#include <functional>
#include <algorithm>

#include "Config.h"
#include "Utilities.h"
#include "Interpretable.h"
#include "SoundGene.h"

#include "Interpreter.h"

namespace IESFX
{
	class SoundData : public Interpretable
	{
	public:
		SoundData();
		~SoundData();

		std::vector<sf::Int16>& operator()(const SoundGene& gene);

	protected:
		void read_poke(RESID::reg8 offset, RESID::reg8 value) override;
		void read_sample(size_t size) override;

	private:
		void poke(RESID::reg8 offset, RESID::reg8 value);
		void sample(size_t size);

		void enqueue(std::function<void()> action)
		{
			_commands.push_back(action);
		}

	private:
		RESID::SID* _sid;

		std::vector<std::function<void()>> _commands;
		std::vector<sf::Int16> _samples;

		size_t _size;
		int _index;
	};
}