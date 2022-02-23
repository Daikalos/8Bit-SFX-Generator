#pragma once

#include <resid/siddefs.h>
#include <string>
#include <vector>
#include <numeric>
#include <utility>
#include <memory>
#include <map>
#include <sstream>

#include "Interpretable.h"

namespace IESFX
{
	struct Command
	{
		Command(int i) 
			: index(i) { }

		virtual std::string print() const = 0;

		int index;
	};

	struct Poke : public Command
	{ 
		Poke(int i, RESID::reg8 o, RESID::reg8 v) 
			: Command(i), offset(o), value(v) { }

		std::string print() const override
		{
			return std::string("poke " + 
				std::to_string(offset) + " " + 
				std::to_string(value));
		}

		RESID::reg8 offset, value;
	};
	struct Sample : public Command
	{ 
		Sample(int i, size_t s)
			: Command(i), size(s) { }

		std::string print() const override
		{
			return std::string("sample " + std::to_string(size));
		}

		size_t size;
	};

	class SoundGene : public Interpretable
	{
	public:
		SoundGene() = default;
		~SoundGene() = default;

		auto& get(int index)
		{
			return _gene[index];
		}

		void set(Poke&& poke)
		{
			_gene[poke.index] = std::make_unique<Poke>(poke);
		}
		void set(Sample&& sample)
		{
			_gene[sample.index] = std::make_unique<Sample>(sample);
		}

		void swap(int x, int y)
		{
			get(x).swap(get(y));
		}

		std::string output()
		{
			std::string output;

			for (const auto& s : _gene)
				output += s.second->print() + '\n';

			return output;
		}

	private:
		std::map<int, std::unique_ptr<Command>> _gene;
	};
}
