#pragma once

namespace IESFX
{
	struct Interpretable
	{
		Interpretable() { }
		virtual ~Interpretable() { }

		virtual void read_poke(unsigned int offset, unsigned int value) = 0;
		virtual void read_sample(size_t size) = 0;
	};
}