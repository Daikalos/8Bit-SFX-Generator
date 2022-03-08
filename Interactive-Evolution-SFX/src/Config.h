#pragma once

#include <resid/siddefs.h>

namespace IESFX
{
	static const RESID::chip_model CHIP_MODEL = RESID::chip_model::MOS6581;

	static const size_t CLOCK_FREQ = 985248;
	static const size_t SAMPLE_RATE = 44100;

	static const size_t CLOCKS_PER_SAMPLE = round(CLOCK_FREQ / (double)SAMPLE_RATE);

	static const size_t POPULATION_SIZE = 360;
	static const size_t GENERATIONS = 100;
	static const double QUALITY = 1000.0;
	static const double COMMAND_MUTATION_CHANCE = 0.05;
	static const double OFFSET_MUTATION_CHANCE = 0.05;
}
