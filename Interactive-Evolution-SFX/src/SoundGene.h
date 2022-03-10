#pragma once

#include <resid/siddefs.h>
#include <string>
#include <vector>
#include <numeric>
#include <utility>
#include <memory>
#include <sstream>

#ifdef NATIVE_CODE
#include <execution>
#endif

#include "Interpretable.h"

namespace IESFX
{
	struct Command
	{
		Command() { }
		virtual ~Command() { }

		virtual std::string print() const = 0;
		virtual std::shared_ptr<Command> clone() const = 0;
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
		std::shared_ptr<Command> clone() const override
		{
			return std::make_shared<Poke>(*this);
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
		std::shared_ptr<Command> clone() const override
		{
			return std::make_shared<Sample>(*this);
		}

		size_t size;
	};

	class SoundGene : public Interpretable
	{
	public:
		SoundGene() = default;
		~SoundGene() = default;

		SoundGene(const SoundGene& rhs);

		void resize(const size_t size);
		void shrink();

		size_t size() const noexcept { return _gene.size(); }

		auto begin() { return _gene.begin(); }
		auto end()	 { return _gene.end(); }

		Command* get(int index) const noexcept { return _gene[index].get(); }
		Command* get(int index) noexcept	   { return _gene[index].get(); }

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

		std::string output() const;

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
		bool _dead{false};

		friend class Evolution;
	};
}
