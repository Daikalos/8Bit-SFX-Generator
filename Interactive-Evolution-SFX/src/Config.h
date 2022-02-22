#pragma once

#include <resid/siddefs.h>

namespace IESFX
{
	static const RESID::chip_model CHIP_MODEL = RESID::chip_model::MOS6581;

	static const size_t CLOCK_FREQ = 985248;
	static const size_t SAMPLE_RATE = 44100;

	static const size_t CLOCKS_PER_SAMPLE = round(CLOCK_FREQ / (double)SAMPLE_RATE);

	static const size_t POPULATION_SIZE = 150;
}
