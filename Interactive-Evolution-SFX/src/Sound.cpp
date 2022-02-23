#include "Sound.h"

using namespace IESFX;

void Sound::reset()
{
	_sound.resetBuffer();
}

void Sound::create_buffer(SoundData& data)
{
	reset();

	std::vector<sf::Int16> buffer(data.buffer());

	_buffer.loadFromSamples(buffer.data(), buffer.size(), 1, SAMPLE_RATE);
	_sound.setBuffer(_buffer);
}

void Sound::load_buffer(const sf::Int16* samples, sf::Uint64 sample_count, unsigned int channel_count, unsigned int sample_rate)
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

bool Sound::save(const std::string& filename)
{
	if (_buffer.getSamples() == nullptr || filename.empty())
		return false;

	return _buffer.saveToFile(filename);
}
