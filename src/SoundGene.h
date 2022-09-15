//  ---------------------------------------------------------------------------
//  This file is part of the 8-Bit SFX Generator
//	Copyright (C) 2022 Tobias Garpenhall <tobiasgarpenhall@gmail.com>
//
//	This program is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	(at your option) any later version.
//	
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//	GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with this program. If not, see <http://www.gnu.org/licenses/>.
//  ---------------------------------------------------------------------------

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
	class SoundGene final : public Interpretable
	{
	public:
		SoundGene() = default;

		SoundGene(const SoundGene& rhs);
		SoundGene(SoundGene&& rhs) noexcept;

		SoundGene& operator=(const SoundGene& rhs);

		bool operator<(const SoundGene& rhs) const;
		bool operator>(const SoundGene& rhs) const;
		bool operator==(const SoundGene& rhs) const;

	public:
		size_t size() const;

		void resize(const std::size_t size);
		void shrink();

		bool exists(std::size_t index) const;

		template<class T = Command, std::enable_if_t<std::is_base_of_v<Command, T>, bool> = true>
		const T& get(const std::size_t index) const;
		template<class T = Command, std::enable_if_t<std::is_base_of_v<Command, T>, bool> = true>
		T& get(const std::size_t index);

		void push(const Poke& poke);
		void push(const Sample& sample);

		void set(const std::size_t index, std::nullptr_t);
		void set(const std::size_t index, const unsigned int offset, const unsigned int value);
		void set(const std::size_t index, const std::size_t size);
		void set(const std::size_t index, const Command& cmd);

		void insert(const std::size_t pos, const Command& command);

		void flip(const std::size_t index);

		auto begin() noexcept { return _gene.begin(); }
		auto end() noexcept { return _gene.end(); }

		auto begin() const noexcept { return _gene.begin(); }
		auto end() const noexcept { return _gene.end(); }

	public:
		std::string print() const;
		std::vector<std::tuple<int, int, int>> range() const;

	private:
		void read_poke(unsigned int offset, unsigned int value) override;
		void read_sample(size_t size) override;

	private:
		std::vector<Command::Ptr> _gene;
		double _fitness{0.0};
		bool _dead{false};

		friend class Evolution;
	};

	template<class T, std::enable_if_t<std::is_base_of_v<Command, T>, bool>>
	const T& SoundGene::get(const std::size_t index) const
	{
		return *static_cast<const T*>(_gene[index].get());
	}
	template<class T, std::enable_if_t<std::is_base_of_v<Command, T>, bool>>
	T& SoundGene::get(const std::size_t index)
	{
		return *static_cast<T*>(_gene[index].get());
	}
}
