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

		SoundGene(const SoundGene& rhs)
		{
			_fitness = rhs._fitness;
			for (size_t i = 0; i < rhs.size(); ++i)
			{
				Poke* poke = dynamic_cast<Poke*>(rhs.get(i));
				Sample* sample = dynamic_cast<Sample*>(rhs.get(i));

				if (poke != nullptr)		push(*poke);
				else if (sample != nullptr) push(*sample);
			}
		}

		auto begin() { return _gene.begin(); }
		auto end()	 { return _gene.end(); }

		Command* get(int index) const noexcept { return _gene[index].get(); }
		Command* get(int index) noexcept	   { return _gene[index].get(); }

		size_t size() const noexcept { return _gene.size(); }

		void resize(const size_t size)
		{
			_gene.resize(size);
		}
		void shrink()
		{
			_gene.erase(std::remove_if(_gene.begin(), _gene.end(), 
				[](std::shared_ptr<Command>& command) 
				{
					return command.get() == nullptr;
				}), _gene.end());
		}

		void set(int index, std::nullptr_t)
		{
			_gene[index].reset();
		}
		void set(int index, unsigned int offset, unsigned int value)
		{
			Poke* poke = static_cast<Poke*>(_gene[index].get());

			poke->offset = offset;
			poke->value = value;
		}
		void set(int index, size_t size)
		{
			static_cast<Sample*>(_gene[index].get())->size = size;
		}
		void set(int index, Command* command)
		{
			(*_gene[index].get()) = *command;
		}

		void push(const Poke& poke)
		{
			_gene.push_back(std::make_shared<Poke>(poke));
		}
		void push(const Sample& sample)
		{
			_gene.push_back(std::make_shared<Sample>(sample));
		}

		void swap(int x, int y)
		{
			_gene[x].swap(_gene[y]);
		}

		std::string output() const
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
		double _fitness{0.0};

		friend class Evolution;
	};
}
