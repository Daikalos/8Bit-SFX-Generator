#pragma once

#include <resid/siddefs.h>

namespace IESFX
{
	const RESID::chip_model CHIP_MODEL = RESID::chip_model::MOS6581;

	const size_t CLOCK_FREQ = 985248;
	const size_t SAMPLE_RATE = 44100;

	const size_t CLOCKS_PER_SAMPLE = round(985248 / (double)44100);

	const size_t POPULATION_SIZE = 150;
}
