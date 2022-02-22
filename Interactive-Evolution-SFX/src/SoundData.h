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
		SoundData() : _size(0), _index(0), _queue(0) { }
		~SoundData() = default;

		// can only be called once
		//
		std::vector<sf::Int16> release()
		{
			_sid = new RESID::SID();
			{
				_sid->set_chip_model(CHIP_MODEL);

				_sid->enable_filter(true);
				_sid->enable_external_filter(true);
			}

			size_t buffer_size = util::get_size(_size);
			_samples.resize(buffer_size, 0);

			_index = 0;

			while (!write_queue.empty() || !sample_queue.empty())
			{
				if (write_queue.empty())
				{
					while (!sample_queue.empty())
					{
						auto smpl = sample_queue.front();
						sample(std::get<1>(smpl));
						sample_queue.pop();
					}
					break;
				}
				else if (sample_queue.empty())
				{
					while (!sample_queue.empty())
					{
						auto wrt = write_queue.front();
						write(std::get<1>(wrt), std::get<2>(wrt));
						write_queue.pop();
					}
					break;
				}
				else
				{
					auto wrt = write_queue.front();
					auto smpl = sample_queue.front();

					if (wrt._Myfirst._Val < smpl._Myfirst._Val)
					{
						write(std::get<1>(wrt), std::get<2>(wrt));
						write_queue.pop();
					}
					else
					{
						sample(std::get<1>(smpl));
						sample_queue.pop();
					}
				}
			}

			size_t length = (_size < 1024LLU) ? _size : 1024LLU;
			for (size_t i = 0; i < length; ++i)
				_samples[i] = 0;

			delete _sid;
			return _samples;
		}

		void enqueue_write(RESID::reg8 offset, RESID::reg8 value)
		{
			write_queue.push(std::make_tuple(_queue++, offset, value));
		}
		void enqueue_sample(size_t size)
		{
			sample_queue.push(std::make_tuple(_queue++, size));
		}

	private:
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

		std::queue<std::tuple<int, RESID::reg8, RESID::reg8>> write_queue;
		std::queue<std::tuple<int, size_t>> sample_queue;

		std::vector<sf::Int16> _samples;
		size_t _index, _queue;
	};
}