#pragma once

#include <vector>
#include <SFML/Audio.hpp>

#include "Config.h"
#include "SoundInfo.h"

namespace IESFX
{
	class Sound
	{
	public:
		Sound();
		~Sound();

		void reset();
		void write(int offset, int value);

		// only generate buffer after write
		//
		void generate_buffer(size_t length);

		void load_buffer(const sf::Int16* samples, Uint64 sample_count, unsigned int channel_count = 1, unsigned int sample_rate = SAMPLE_RATE);

		sf::SoundSource::Status status() const;
		void set_volume(double volume);

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