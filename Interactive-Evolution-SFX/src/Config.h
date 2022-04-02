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
	static const RESID::chip_model CHIP_MODEL = RESID::chip_model::MOS6581;

	static const size_t CLOCK_FREQ = 985248;
	static const size_t SAMPLE_RATE = 44100;

	static const size_t CLOCKS_PER_SAMPLE = static_cast<size_t>(round(CLOCK_FREQ / (double)SAMPLE_RATE));

	static const size_t ROWS = 3;
	static const size_t COLUMNS = 4;

	static const size_t POPULATION_SIZE = 1400;
	static const size_t USABLE_POPULATION = 600;
	static const size_t GENERATIONS = 100;
	static const double QUALITY = 3.1;

	static const int N_POINTS = 3;
	static const size_t MODEL_SAMPLES = 3;

	static const double REMOVE_MUTATION = 0.075;
	static const double ADD_MUTATION = 0.075;
	static const double COMMAND_MUTATION = 0.1;
	static const double OFFSET_MUTATION = 0.1;

	static const RESID::reg8 POKE_OFFSET = 23;
	static const RESID::reg8 POKE_MIN_VALUE = 1;
	static const RESID::reg8 POKE_MAX_VALUE = 140;
	static const size_t MIN_SAMPLE_SIZE = 256;
	static const size_t MAX_SAMPLE_SIZE = 1400;

	static const size_t AVERAGE_SAMPLE = 512;

	#define BUILD true
}
