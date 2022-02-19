#pragma once

#include <vector>
#include <SFML/Audio.hpp>

#include <resid/sid.h>

#include "Config.h"
#include "SoundInfo.h"
#include "Utilities.h"

namespace IESFX
{
	class Sound
	{
	public:
		Sound();
		~Sound();

		void reset();

		// only create buffer after write
		//
		void create_buffer(const SoundInfo& info);

		void load_buffer(const sf::Int16* samples, sf::Uint64 sample_count, unsigned int channel_count = 1, unsigned int sample_rate = SAMPLE_RATE);

		sf::SoundSource::Status status() const;
		void set_volume(double volume);

		double length() const { return _length; }

		void play();
		void pause();
		void stop();

	private:
		size_t _length;
		size_t _buffer_size;

		sf::Sound _sound;
		sf::SoundBuffer _buffer;

		RESID::SID _sid;
	};
}