#pragma once

namespace IESFX
{
	struct SoundInfo
	{
		unsigned int reg[24];

		unsigned int& operator[](int i) { return reg[i]; }
		unsigned int operator[](int i) const { return reg[i]; }
	};
}