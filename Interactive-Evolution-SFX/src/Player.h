#pragma once

#include <iostream>
#include <vector>
#include <functional>
#include <fstream>
#include <thread>
#include <msclr/marshal_cppstd.h>

#include <SFML/Audio.hpp>

#include "Sound.h"
#include "Config.h"
#include "Utilities.h"
#include "Evolution.h"

namespace IESFX
{
	using namespace System;
	using namespace System::Threading;
	using namespace System::IO;

	public ref class Player
	{
	public:
		Player(Evolution* evolution, size_t size, double volume);
		~Player();

		void initialize();

		void reset();

		void set_volume(double volume);
		void set_is_playing(bool value);

		Sound* play(size_t id);

		void play();
		void pause();

		void iterate();

		bool load(String^ file);
		bool save(String^ name);

		void update(const std::vector<SoundGene>& info);

		int position() { return _position; }
		bool active() { return _is_playing; }

		Sound* operator[](int i)
		{
			return &_sounds[i];
		}

	public:
		delegate void callback_play(); // called everytime a sound is played
		delegate void callback_done(); // called when reached end
		delegate void callback_update(Sound*, int);

		callback_play^ _callback_play;
		callback_done^ _callback_done;
		callback_update^ _callback_update;

	private:
		void player_loop();

		bool load_wav(String^ file);
		bool load_txt(String^ file);

	private:
		size_t _position, _size;
		bool _is_playing, _shutdown;
		double _volume;

		Evolution* _evolution;

		Sound* _sounds;
		Sound* _sound;

		Thread^ _thread;
	};
}

