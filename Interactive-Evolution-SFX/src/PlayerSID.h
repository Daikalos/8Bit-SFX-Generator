#pragma once

#include <resid/sid.h>
#include <SDL_audio.h>

#include <iostream>
#include <vector>

class PlayerSID
{
public:
	PlayerSID();
	~PlayerSID();

	void set_volume(double volume);

	void play();
	void pause();

private:
	RESID::SID* _sid;
	std::vector<int>* _buffer;

	double _volume;
	bool _is_playing;

	int _sdl_device;
	SDL_AudioSpec* _soundspec;
};

