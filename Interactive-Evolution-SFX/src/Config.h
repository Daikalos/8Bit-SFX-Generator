#pragma once

#include <SDL.h>
#include <resid/sid.h>

namespace IESFX
{
	const size_t C64_PAL_CPUCLK = 985248;
	const RESID::chip_model CHIP_MODEL = RESID::chip_model::MOS6581;

	const size_t FORMAT = AUDIO_U8;
	const size_t SAMPLE_RATE = 44100;
}
