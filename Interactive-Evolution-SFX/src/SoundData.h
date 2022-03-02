#pragma once

#include <resid/sid.h>
#include <SFML/Config.hpp>
#include <vector>
#include <functional>
#include <algorithm>

#include "Config.h"
#include "Utilities.h"
#include "Interpretable.h"
#include "SoundGene.h"

#include "Interpreter.h"

namespace IESFX
{
	class SoundData : public Interpretable
	{
	public:
		SoundData() 
			: _sid(new RESID::SID()), _size(0), _index(0) 
		{ 
			_sid->set_chip_model(CHIP_MODEL);

			_sid->enable_filter(true);
			_sid->enable_external_filter(true);
		}
		~SoundData()
		{
			delete _sid;
		}

		std::vector<sf::Int16> buffer(const SoundGene& gene)
		{
			_sid->reset();
			_samples.clear();
			_commands.clear();

			Interpreter().read_str(this, gene.output());

			_samples.resize(util::get_size(_size), 0);
			_index = 0;

			for (auto& comm : _commands)
				comm();

#if !_DEBUG
			size_t length = std::min<size_t>(_samples.size(), 1024LLU);
			for (size_t i = 0; i < length; ++i)
				_samples[i] = 0;
#endif

			return _samples;
		}

	protected:
		void read_poke(RESID::reg8 offset, RESID::reg8 value) override
		{
			enqueue(std::bind(&SoundData::poke, this, offset, value));
		}
		void read_sample(size_t size) override
		{
			_size += size;
			enqueue(std::bind(&SoundData::sample, this, size));
		}

	private:
		void enqueue(std::function<void()> action)
		{
			_commands.push_back(action);
		}

		void poke(RESID::reg8 offset, RESID::reg8 value)
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

		std::vector<std::function<void()>> _commands;
		size_t _index;

		std::vector<sf::Int16> _samples;
	};
}