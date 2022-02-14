#pragma once

#include <iostream>
#include <vector>
#include <functional>
#include <fstream>
#include <thread>

#include <SFML/Audio.hpp>


#include "utilities.h"
#include "Config.h"
#include "Sound.h"

namespace IESFX
{
	using namespace System::Threading;

	public ref class Player
	{
	public:
		Player(std::vector<Sound>* sounds);
		~Player();

		void reset();

		void set_volume(double volume);

		void play();
		void pause();

		void iterate();

		void play_sound(const Sound& sound);

		bool load(const std::string& file);
		bool save(const std::string& name);

		int pos() { return _pos; }

		Sound* operator[](int i)
		{
			return &_sounds->at(i);
		}

	public:
		delegate void callback_play(); // called everytime a sound is played
		delegate void callback_done(); // called when reached end

		callback_play^ _callback_play;
		callback_done^ _callback_done;

	private:
		void player_loop();

	private:
		std::vector<Sound>* _sounds;
		Sound* _sound;

		bool _is_playing, _shutdown;
		double _volume;
		int _pos;

		Thread^ _thread;
	};
}

