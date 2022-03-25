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

		std::vector<sf::Int16>& operator()(const SoundGene& gene)
		{
			Interpreter().read_str(this, gene.output());
			_samples.resize(util::get_size(_size), 0);

			for (auto& comm : _commands)
				comm();

#if !_DEBUG
			memset(_samples.data(), 0, std::min<size_t>(_samples.size(), 1024LLU));
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

	private:
		RESID::SID* _sid;

		std::vector<std::function<void()>> _commands;
		std::vector<sf::Int16> _samples;

		size_t _size, _index;
	};
}