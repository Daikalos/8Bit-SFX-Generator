#pragma once

#include <resid/sid.h>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <queue>
#include <SFML/Config.hpp>

#include "Config.h"
#include "Utilities.h"

namespace IESFX
{
	class SoundData
	{
	public:
		SoundData() 
			: _sid(new RESID::SID()), _size(0), _index(0), _queue(0) 
		{ 
			_sid->set_chip_model(CHIP_MODEL);

			_sid->enable_filter(true);
			_sid->enable_external_filter(true);
		}
		~SoundData()
		{
			delete _sid;
		}

		std::vector<sf::Int16> buffer()
		{
			_sid->reset();

			size_t buffer_size = util::get_size(_size);
			_samples.resize(buffer_size, 0);

			_index = 0;

			for (auto& func : actions)
				func();

			size_t length = (_size < 1024LLU) ? _size : 1024LLU;
			for (size_t i = 0; i < length; ++i)
				_samples[i] = 0;

			return _samples;
		}

		void enqueue(std::function<void()> action)
		{
			actions.push_back(action);
		}

		void write(RESID::reg8 offset, RESID::reg8 value)
		{
			_sid->write(offset, value);
		}
		void sample(size_t size)
		{
			RESID::cycle_count delta_t = util::get_cycles(util::get_size(size));
			_index += _sid->clock(delta_t, _samples.data() + _index, util::get_size(size));
		}

	public:
		size_t _size;

	private:
		RESID::SID* _sid;

		std::vector<std::function<void()>> actions;

		std::vector<sf::Int16> _samples;
		size_t _index, _queue;
	};
}