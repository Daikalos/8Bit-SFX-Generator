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
		SoundData();
		~SoundData();

		std::vector<sf::Int16>& operator()(const SoundGene& gene);

	protected:
		void read_poke(RESID::reg8 offset, RESID::reg8 value) override;
		void read_sample(size_t size) override;

	private:
		void poke(RESID::reg8 offset, RESID::reg8 value);
		void sample(size_t size);

		void enqueue(std::function<void()> action)
		{
			_commands.push_back(action);
		}

	private:
		RESID::SID* _sid;

		std::vector<std::function<void()>> _commands;
		std::vector<sf::Int16> _samples;

		size_t _size, _index;
	};
}