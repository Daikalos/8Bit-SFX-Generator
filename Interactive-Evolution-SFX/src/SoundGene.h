#pragma once

#include <resid/sid.h>
#include <string>

namespace IESFX
{
	struct SoundGene
	{
		SoundGene() { memset(reg, 0, sizeof(reg)); }
		~SoundGene() = default;

		unsigned int reg[25];
		double length = 1;

		unsigned int& operator[](int i) { return reg[i]; }
		unsigned int operator[](int i) const { return reg[i]; }
	};
}