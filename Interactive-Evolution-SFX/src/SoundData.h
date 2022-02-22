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
		SoundData()
		{
			_sid.set_chip_model(CHIP_MODEL);

			_sid.enable_filter(true);
			_sid.enable_external_filter(true);
		}
		~SoundData() = default;

		void write(short offset, short value)
		{
			_sid.write(offset, value);
		}

		std::vector<sf::Int16> samples()
		{
			size_t buffer_size = SAMPLE_RATE * 1;
			std::vector<sf::Int16> samples(buffer_size, 0);

			//_sid.write(1, 130);
			//_sid.write(5, 9);
			//_sid.write(15, 30);
			//_sid.write(24, 15);

			//int index = 0;
			//for (int l = 0; l < 12; ++l)
			//{
			//	_sid.write(4, 22);

			//	for (int i = 0; i < 1000; ++i)
			//	{
			//		_sid.clock(CLOCKS_PER_SAMPLE);
			//		samples[index] = _sid.output();

			//		++index;
			//	}

			//	_sid.write(l, 15);

			//	for (int i = 0; i < 1000; ++i)
			//	{
			//		_sid.clock(CLOCKS_PER_SAMPLE);
			//		samples[index] = _sid.output();

			//		++index;
			//	}
			//}

			RESID::cycle_count delta_t = util::get_cycles(buffer_size);
			_sid.clock(delta_t, samples.data(), buffer_size);

			return samples;
		}

	private:
		RESID::SID _sid;
	};
}