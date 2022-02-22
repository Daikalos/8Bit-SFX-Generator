#pragma once

#include <resid/sid.h>
#include <string>
#include <vector>
#include <SFML/Config.hpp>

#include "Config.h"
#include "Utilities.h"

namespace IESFX
{
	class SoundData
	{
	public:
		SoundData() { memset(reg, 0, sizeof(reg)); }
		~SoundData() = default;

		unsigned int reg[25];

		unsigned int& operator[](int i) { return reg[i]; }
		unsigned int operator[](int i) const { return reg[i]; }

		std::vector<sf::Int16> samples()
		{
			RESID::SID sid;

			size_t buffer_size = SAMPLE_RATE * 1;
			std::vector<sf::Int16> samples(buffer_size, 0);

			{
				sid.set_chip_model(CHIP_MODEL);

				sid.enable_filter(true);
				sid.enable_external_filter(true);

				for (int i = 0; i < 25; ++i)
					sid.write(i, reg[i]);
			}

			sid.write(1, 130);
			sid.write(5, 9);
			sid.write(15, 30);
			sid.write(24, 15);

			int index = 0;

			sid.write(4, 21);

			{
				RESID::cycle_count delta_t = util::get_cycles(1000 * CLOCKS_PER_SAMPLE);
				index += sid.clock(delta_t, samples.data() + index, 1000 * CLOCKS_PER_SAMPLE);
			}

			sid.write(4, 20);

			{
				RESID::cycle_count delta_t = util::get_cycles(1000 * CLOCKS_PER_SAMPLE);
				index += sid.clock(delta_t, samples.data() + index, 1000 * CLOCKS_PER_SAMPLE);
			}

			//RESID::cycle_count delta_t = util::get_cycles(buffer_size);
			//_sid->clock(delta_t, samples->data(), buffer_size);

			for (int i = 0; i < 1024; ++i)
				samples[i] = 0;

			return samples;
		}
	};
}