#pragma once

namespace IESFX
{
	struct SoundInfo
	{
		SoundInfo() { memset(reg, 0, sizeof(reg)); }
		~SoundInfo() = default;

		unsigned int reg[25];

		unsigned int& operator[](int i) { return reg[i]; }
		unsigned int operator[](int i) const { return reg[i]; }
	};
}