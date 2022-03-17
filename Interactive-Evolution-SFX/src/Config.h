#pragma once

#include <resid/siddefs.h>

namespace IESFX
{
	static const RESID::chip_model CHIP_MODEL = RESID::chip_model::MOS6581;

	static const size_t CLOCK_FREQ = 985248;
	static const size_t SAMPLE_RATE = 44100;

	static const size_t CLOCKS_PER_SAMPLE = round(CLOCK_FREQ / (double)SAMPLE_RATE);

	static const size_t POPULATION_SIZE = 1800;
	static const size_t GENERATIONS = 60;
	static const double QUALITY = 2.00;

	static const int N_POINTS = 3;
	static const size_t MODEL_SAMPLES = 1;

	static const double REMOVE_MUTATION = 0.05;
	static const double ADD_MUTATION = 0.05;
	static const double COMMAND_MUTATION = 0.05;
	static const double OFFSET_MUTATION = 0.05;

	static const RESID::reg8 POKE_OFFSET = 23;
	static const RESID::reg8 POKE_VALUE = 120;
	static const size_t MIN_SAMPLE_SIZE = 128;
	static const size_t MAX_SAMPLE_SIZE = 1400;

	static const size_t AVERAGE_SAMPLE = 32;
}
