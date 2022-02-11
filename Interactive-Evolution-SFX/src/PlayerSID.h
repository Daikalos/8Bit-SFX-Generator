#pragma once

#include <resid/sid.h>
#include <SDL.h>

#include <iostream>
#include <vector>

#include <fstream>

const size_t SAMPLE_RATE = 44100;
const RESID::chip_model CHIP_MODEL = RESID::chip_model::MOS6581;

class PlayerSID
{
public:
	PlayerSID();
	~PlayerSID();

	void set_volume(double volume);

	void play();
	void pause();

	bool load(const std::string& file);

private:
	static void sdl_callback(void*, unsigned char*, int);

private:
	RESID::SID* _sid;
	std::vector<unsigned char>* _buffer;

	double _volume;
	bool _is_playing;

	int _sdl_device;
	SDL_AudioSpec* _audio_spec;
};

