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
#include <SFML/Audio.hpp>
#include <filesystem>

#include <resid/sid.h>

#include "Config.h"
#include "SoundData.h"
#include "SoundGene.h"
#include "Utilities.h"

namespace IESFX
{
	class Sound final
	{
	public:
		// only create buffer after write
		//
		void create_buffer(const SoundGene& gene);
		void load_buffer(const sf::Int16* samples, sf::Uint64 sample_count, unsigned int channel_count = 1, unsigned int sample_rate = SAMPLE_RATE);

		sf::SoundSource::Status status() const;
		void set_volume(float volume);

		void play();
		void pause();
		void stop();

		const SoundGene& get() const;

		const sf::Int16* buffer_samples() const;
		sf::Uint64 buffer_count() const;

		float time() const;
		float duration() const;

		bool save(const std::string& filename) const;
		bool save_wav(const std::string& filename) const;
		bool save_txt(const std::string& filename) const;

	private:
		sf::Sound _sound;
		sf::SoundBuffer _buffer;

		const SoundGene* _gene;
	};
}