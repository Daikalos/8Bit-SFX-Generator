#include "PlayerSID.h"

PlayerSID::PlayerSID()
{
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
		throw std::runtime_error("error initializing SDL");

	_audio_spec = new SDL_AudioSpec();
	_audio_spec->freq = SAMPLE_RATE;
	_audio_spec->channels = 1;
	_audio_spec->format = AUDIO_S8;
	_audio_spec->samples = 32768;
	_audio_spec->userdata = nullptr;
	_audio_spec->callback = sdl_callback;

	_sdl_device = SDL_OpenAudioDevice(nullptr, 0, _audio_spec, nullptr, SDL_AUDIO_ALLOW_FORMAT_CHANGE);

	if (!_sdl_device)
		throw std::runtime_error("could not open SDL audio");

	_sid = new RESID::SID();
	_sid->set_chip_model(CHIP_MODEL);

	_buffer = new std::vector<unsigned char>();
}

PlayerSID::~PlayerSID()
{
	pause();
	SDL_CloseAudioDevice(_sdl_device);

	delete _sid;
	delete _buffer;
	delete _audio_spec;
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

bool PlayerSID::load(const std::string& file)
{
	pause();
	_buffer->clear();

	std::ifstream stream(file.c_str(), std::ios::binary);

	if (stream)
	{
		stream.seekg(0, stream.end);
		_buffer->resize(stream.tellg());
		stream.seekg(0, stream.beg);

		stream.read((char*)_buffer->data(), _buffer->size());

		libcsid_load(buffer.data(), buffer.size(), subtune);

		if (!_buffer->empty())
			return true;
	}

	return true;
}

void PlayerSID::sdl_callback(void* userdata, unsigned char* stream, int length)
{

}
