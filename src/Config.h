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

namespace IESFX
{
	constexpr RESID::chip_model CHIP_MODEL = RESID::chip_model::MOS6581;

	constexpr std::size_t CLOCK_FREQ = 985248;
	constexpr std::size_t SAMPLE_RATE = 44100;

	constexpr std::size_t SAMPLES_PER_CLOCK = static_cast<size_t>(CLOCK_FREQ / (double)SAMPLE_RATE);

	constexpr std::size_t ROWS = 3;
	constexpr std::size_t COLUMNS = 4;

	constexpr std::size_t POPULATION_SIZE = 1800;
	constexpr std::size_t USABLE_POPULATION = 960;
	constexpr std::size_t GENERATIONS = 80;
	constexpr double QUALITY = 3.0;

	constexpr int N_POINTS = 3;
	constexpr std::size_t MODEL_SAMPLES = 3;

	constexpr double REMOVE_MUTATION = 0.075;
	constexpr double ADD_MUTATION = 0.075;
	constexpr double COMMAND_MUTATION = 0.1;
	constexpr double OFFSET_MUTATION = 0.1;

	constexpr RESID::reg8 POKE_OFFSET = 23;
	constexpr RESID::reg8 POKE_MIN_VALUE = 1;
	constexpr RESID::reg8 POKE_MAX_VALUE = 140;
	constexpr std::size_t MIN_SAMPLE_SIZE = 256;
	constexpr std::size_t MAX_SAMPLE_SIZE = 1400;

	constexpr std::size_t AVERAGE_SAMPLE = 512;

	#define BUILD true
}
