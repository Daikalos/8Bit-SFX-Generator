#include "PlayerSID.h"

PlayerSID::PlayerSID()
	: _sid(nullptr), _buffer(nullptr), _volume(0.5), _is_playing(false), _sdl_device(0), _audio_spec(nullptr)
{
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
		throw std::runtime_error(SDL_GetError());

	_audio_spec = new SDL_AudioSpec();
	_audio_spec->freq = SAMPLE_RATE;
	_audio_spec->channels = 1;
	_audio_spec->format = AUDIO_S8;
	_audio_spec->samples = 32768;
	_audio_spec->callback = sdl_callback;
	_audio_spec->userdata = this;

	_sdl_device = SDL_OpenAudioDevice(nullptr, 0, _audio_spec, nullptr, SDL_AUDIO_ALLOW_FORMAT_CHANGE);

	if (!_sdl_device)
		throw std::runtime_error(SDL_GetError());

	_sid = new RESID::SID();
	_sid->set_chip_model(CHIP_MODEL);
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
	if (_is_playing) //|| _buffer->empty())
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

	std::ifstream stream(file, std::ios::binary);

	if (stream.is_open())
	{
		if (_buffer != nullptr)
			delete _buffer;

		std::istream_iterator<char> start(stream), end;
		_buffer = new std::vector<unsigned char>(start, end);

		int size = _buffer->size();

		 //while (delta_t) 
		 //{
		 //  bufindex += sid.clock(delta_t, buf + bufindex, buflength - bufindex);
		 //  write(dsp, buf, bufindex*2);
		 //  bufindex = 0;
		 //}

		stream.close();

		if (!_buffer->empty())
			return true;
	}

	return true;
}

void PlayerSID::sdl_callback(void* userdata, unsigned char* stream, int length)
{
	PlayerSID* player = static_cast<PlayerSID*>(userdata);
	RESID::SID* sid = player->_sid;

	extern SDL_AudioFormat deviceFormat;
	extern const Uint8* mixData;
	
	SDL_memset(stream, 0, length);
	SDL_MixAudioFormat(stream, mixData, deviceFormat, length, SDL_MIX_MAXVOLUME * player->_volume); // set volume

	sid->reset();

	sid->write(0, 100);
	sid->write(5, 219);
	sid->write(15, 28);

	sid->clock(delta_t, reinterpret_cast<short*>(stream), length);
}
