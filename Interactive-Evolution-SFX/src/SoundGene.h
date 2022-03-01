#pragma once

#include <resid/siddefs.h>
#include <string>
#include <vector>
#include <numeric>
#include <utility>
#include <memory>
#include <sstream>

#include "Interpretable.h"

namespace IESFX
{
	struct Command
	{
		Command() { }
		virtual ~Command() { }

		virtual std::string print() const = 0;
	};

	struct Poke : public Command
	{ 
		Poke(RESID::reg8 o, RESID::reg8 v) 
			: offset(o), value(v) { }

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
		Sample(size_t s) : size(s) { }

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

		Command* get(int index) const
		{
			return _gene[index].get();
		}
		Command* get(int index)
		{
			return _gene[index].get();
		}

		size_t size() const
		{
			return _gene.size();
		}

		void set(int index, Poke&& poke)
		{
			_gene[index] = std::make_unique<Poke>(poke);
		}
		void set(int index, Sample&& sample)
		{
			_gene[index] = std::make_unique<Sample>(sample);
		}
		void push(Poke&& poke)
		{
			_gene.push_back(std::make_shared<Poke>(poke));
		}
		void push(Sample&& sample)
		{
			_gene.push_back(std::make_shared<Sample>(sample));
		}

		void swap(int x, int y)
		{
			_gene[x].swap(_gene[y]);
		}

		std::string output()
		{
			std::string output;

			for (const auto& s : _gene)
				output += s->print() + '\n';

			return output;
		}

	protected:
		void read_poke(unsigned int offset, unsigned int value) override
		{
			push({ offset, value });
		}
		void read_sample(size_t size) override
		{
			push({ size });
		}

	private:
		std::vector<std::shared_ptr<Command>> _gene;
	};
}
