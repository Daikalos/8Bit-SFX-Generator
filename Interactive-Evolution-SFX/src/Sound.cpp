//  ---------------------------------------------------------------------------
//  This file is part of the 8-Bit SFX Generator
//	Copyright (C) 2022 Tobias Garpenhall
//
//	This program is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	(at your option) any later version.
//	
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//	GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with this program. If not, see <http://www.gnu.org/licenses/>.
//  ---------------------------------------------------------------------------

#include "Sound.h"

using namespace IESFX;

void Sound::create_buffer(SoundGene& gene)
{
	_gene = gene;

	std::vector<sf::Int16> buffer(SoundData()(gene));

	if (buffer.size() <= 128)
		buffer.resize(128, 0);

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
void Sound::set_volume(float volume)
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

bool Sound::save(const std::string& filename) const
{
	if (filename.empty())
		return false;

	std::string ext = std::filesystem::path(filename).extension().string();

	if (ext == ".wav")
		return save_wav(filename);
	if (ext == ".txt")
		return save_txt(filename);

	return false;
}
bool Sound::save_wav(const std::string& filename) const
{
	if (_buffer.getSamples() == nullptr)
		return false;

	return _buffer.saveToFile(filename);
}
bool Sound::save_txt(const std::string& filename) const
{
	if (_gene.size() == 0)
		return false;

	std::ofstream out;
	out.open(filename, std::ofstream::trunc);

	out << "// DO NOT REMOVE OR ADD ANY 'RUN' COMMANDS\n";

	for (size_t i = 0; i < _gene.size(); ++i)
		out << _gene.get(i)->print() + '\n';

	out << "RUN";

	out.close();

	return true;
}
