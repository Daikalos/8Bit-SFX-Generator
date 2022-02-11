#include "PlayerSID.h"

PlayerSID::PlayerSID()
{
	_sid = new RESID::SID();
	_sid->set_chip_model(RESID::chip_model::MOS8580);

	_buffer = new std::vector<int>();
}

PlayerSID::~PlayerSID()
{
	delete _sid;
	delete _buffer;
}

void PlayerSID::set_volume(double volume)
{
	_volume = volume;
}

void PlayerSID::play()
{
	if (_is_playing || _buffer->empty())
		return;

	SDL_PauseAudioDevice(_sdl_device, 0);
	_is_playing = true;
}

void PlayerSID::pause()
{
	if (!_is_playing)
		return;

	SDL_PauseAudioDevice(_sdl_device, 1);
	_is_playing = false;
}
