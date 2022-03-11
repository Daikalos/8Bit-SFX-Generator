#pragma once

#include <vector>
#include <numeric>
#include <utility>
#include <sstream>

#ifdef NATIVE_CODE
#include <execution>
#endif

#include "Interpretable.h"
#include "Command.h"

namespace IESFX
{
	class SoundGene : public Interpretable
	{
	public:
		SoundGene() = default;
		~SoundGene() = default;

		SoundGene(const SoundGene& rhs);

		void resize(const size_t size);
		void shrink();

		std::string output() const;

		SoundGene& operator=(const SoundGene& rhs);

		size_t size() const noexcept { return _gene.size(); }

		auto begin() { return _gene.begin(); }
		auto end()	 { return _gene.end(); }

		Command* get(int index) const noexcept { return _gene[index].get(); }
		Command* get(int index) noexcept	   { return _gene[index].get(); }

		void push(const Poke& poke)		{ _gene.push_back(poke.clone()); }
		void push(const Sample& sample) { _gene.push_back(sample.clone()); }

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

		void flip(int index)
		{
			_gene[index] = get(index)->flip();
		}

		friend bool operator==(const SoundGene& lhs, const SoundGene& rhs)
		{
			if (lhs.size() != rhs.size())
				return false;

			for (size_t i = 0; i < rhs.size(); ++i)
			{
				if (*lhs.get(i) != rhs.get(i))
					return false;
			}

			return true;
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
		bool _dead{false};

		friend class Evolution;
	};
}
