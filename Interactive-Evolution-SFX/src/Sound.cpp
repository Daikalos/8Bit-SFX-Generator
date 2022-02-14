#include "Sound.h"

using namespace IESFX;

Sound::Sound()
	: _length(0), _buffer_size(0)
{
	_sid.set_chip_model(CHIP_MODEL);

	_sid.enable_filter(true);
	_sid.enable_external_filter(true);
}

Sound::~Sound()
{
	
}

void Sound::reset()
{
	_sid.reset();
	_sound.resetBuffer();
}

void Sound::generate_buffer(const SoundInfo& info, size_t length)
{
	reset();

	_length = length;

	for (int i = 0; i < 25; ++i)
		_sid.write(i, info[i]);

	_buffer_size = SAMPLE_RATE * length;
	std::vector<sf::Int16> buffer(_buffer_size);

	for (int i = 0; i < _buffer_size; ++i)
	{
		_sid.clock();
		buffer[i] = _sid.output() << 8;
	}

	_buffer.loadFromSamples(buffer.data(), _buffer_size, 1, SAMPLE_RATE);
	_sound.setBuffer(_buffer);
}

void Sound::load_buffer(const sf::Int16* samples, Uint64 sample_count, unsigned int channel_count, unsigned int sample_rate)
{
	_buffer.loadFromSamples(samples, sample_count, channel_count, sample_rate);
	_sound.setBuffer(_buffer);
}

sf::SoundSource::Status Sound::status() const
{
	return _sound.getStatus();
}
void Sound::set_volume(double volume)
{
	_sound.setVolume(volume * 100);
}

void Sound::play()
{
	_sound.play();
}
void Sound::pause()
{
	_sound.pause();
}
void Sound::stop()
{
	_sound.stop();
}
