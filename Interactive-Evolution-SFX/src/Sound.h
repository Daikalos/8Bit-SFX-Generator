#pragma once

#include <vector>
#include <SFML/Audio.hpp>
#include <filesystem>

#include <resid/sid.h>

#include "Config.h"
#include "SoundData.h"
#include "SoundGene.h"
#include "Utilities.h"

namespace IESFX
{
	class Sound
	{
	public:
		Sound() = default;
		~Sound() = default;

		SoundGene* get() { return &_gene; }

		// only create buffer after write
		//
		void create_buffer(SoundGene& gene);

		void load_buffer(const sf::Int16* samples, sf::Uint64 sample_count, unsigned int channel_count = 1, unsigned int sample_rate = SAMPLE_RATE);

		sf::SoundSource::Status status() const;
		void set_volume(double volume);

		const sf::Int16* buffer_samples() const { return _buffer.getSamples(); }
		sf::Uint64 buffer_count() const { return _buffer.getSampleCount(); }

		void play();
		void pause();
		void stop();

		float time() const { return _sound.getPlayingOffset().asSeconds(); }
		float duration() const { return _buffer.getDuration().asSeconds(); }

		bool save(const std::string& filename) const;
		bool save_wav(const std::string& filename) const;
		bool save_txt(const std::string& filename) const;

	private:
		sf::Sound _sound;
		sf::SoundBuffer _buffer;

		SoundGene _gene;
	};
}