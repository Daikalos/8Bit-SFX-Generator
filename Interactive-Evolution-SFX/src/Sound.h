#pragma once

#include <vector>

#include "Config.h"
#include <SFML/Audio.hpp>

class Sound
{
public:
	Sound();
	~Sound();

	void reset();
	void write(int offset, int value);

	// only create after write
	//
	void create_buffer(size_t length);

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