#pragma once

#include <cppsid/cppsid.h>
#include <resid/sid.h>

#include <iostream>

class PlayerSID
{
public:
	PlayerSID();
	~PlayerSID();

	void set_volume(double volume);

private:
	RESID::SID* _sid;
	std::vector<int>* _buffer;

	double _volume;
	bool _is_playing;

	int _sdl_device;
	SDL_AudioSpec* _soundspec;
};

