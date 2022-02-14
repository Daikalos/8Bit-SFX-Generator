#pragma once

#include <iostream>
#include <vector>

#include <fstream>

#include <SFML/Audio.hpp>

#include <functional>

#include "utilities.h"
#include "Config.h"
#include "Sound.h"

namespace IESFX
{
	public ref class Player
	{
	public:
		Player(std::vector<Sound>* sounds);
		~Player();

		void set_volume(double volume);

		void play();
		void pause();

		void play_sound(const Sound& sound);

		bool load(const std::string& file);
		bool save(const std::string& name);

		int pos() { return _pos; }

		template<class F, class... Args>
		void add_callback_begin(F&& f, Args&&... args)
		{
			_callbacks_begin.push_back(std::bind(
				std::forward<F>(f), std::forward<Args>(args)...));
		}
		template<class F, class... Args>
		void add_callback_end(F&& f, Args&&... args)
		{
			_callbacks_end.push_back(std::bind(
				std::forward<F>(f), std::forward<Args>(args)...));
		}

	private:
		delegate void callback_begin(); // called everytime a sound is started
		delegate void callback_end();   // called when reached end

	public:
		callback_begin^ _callback_begin;
		callback_end^ _callback_end;

	private:
		std::vector<Sound>* _sounds;
		Sound* _sound;

		bool _is_playing;
		double _volume;
		int _pos;
	};
}

