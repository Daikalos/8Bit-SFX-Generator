#pragma once

#include <resid/siddefs.h>

namespace IESFX
{
	static const RESID::chip_model CHIP_MODEL = RESID::chip_model::MOS6581;

	static const size_t CLOCK_FREQ = 985248;
	static const size_t SAMPLE_RATE = 44100;

	static const size_t CLOCKS_PER_SAMPLE = round(CLOCK_FREQ / (double)SAMPLE_RATE);

	static const size_t POPULATION_SIZE = 1800;
	static const size_t GENERATIONS = 100;
	static const double QUALITY = 1500.0;

	static const int N_POINTS = 4;

	static const double COMMAND_MUTATION_CHANCE = 0.05;
	static const double OFFSET_MUTATION_CHANCE = 0.05;

	static const RESID::reg8 POKE_OFFSET = 23;
	static const RESID::reg8 POKE_VALUE = 100;
	static const size_t MIN_SAMPLE_SIZE = 32;
	static const size_t MAX_SAMPLE_SIZE = 1000;
}
