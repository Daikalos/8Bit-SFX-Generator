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

		template<class T, typename std::enable_if_t<std::is_arithmetic_v<T>>* = nullptr>
		std::vector<std::tuple<T, T, T>> range() const
		{
			std::vector<std::tuple<T, T, T>> result;
			for (T i = 0, index = 0; i < size(); ++i)
			{
				if (dynamic_cast<Sample*>(get(i)) != nullptr)
				{
					result.push_back(std::make_tuple(index, i, i - index));
					index = i + 1;
				}
			}
			return result;
		}

		std::string output() const;

		SoundGene& operator=(const SoundGene& rhs);

		size_t size() const noexcept { return _gene.size(); }

		auto begin() { return _gene.begin(); }
		auto end()	 { return _gene.end(); }

		Command* get(size_t index) const noexcept { return _gene[index].get(); }
		Command* get(size_t index) noexcept	   { return _gene[index].get(); }

		void push(const Poke& poke)		{ _gene.push_back(poke.clone()); }
		void push(const Sample& sample) { _gene.push_back(sample.clone()); }

		auto insert(size_t pos, const Poke& poke)
		{
			return _gene.insert(_gene.begin() + pos, poke.clone());
		}

		void set(size_t index, std::nullptr_t)
		{
			_gene[index].reset();
		}
		void set(size_t index, unsigned int offset, unsigned int value)
		{
			Poke* poke = static_cast<Poke*>(_gene[index].get());

			poke->offset = offset;
			poke->value = value;
		}
		void set(size_t index, size_t size)
		{
			static_cast<Sample*>(_gene[index].get())->size = size;
		}
		void set(size_t index, Command* command)
		{
			(*_gene[index].get()) = *command;
		}

		void flip(size_t index)
		{
			if (get(index) != nullptr)
				_gene[index] = get(index)->flip();
		}

		friend bool operator<(const SoundGene& lhs, const SoundGene& rhs)
		{
			return lhs._fitness > rhs._fitness;
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
		std::vector<std::unique_ptr<Command>> _gene;
		double _fitness{0.0};
		bool _dead{false};

		friend class Evolution;
	};
}
