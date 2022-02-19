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

namespace IESFX
{
	using namespace System;
	using namespace System::Threading;
	using namespace System::IO;

	public ref class Player
	{
	public:
		Player(size_t size, double volume);
		~Player();

		void reset();

		void set_volume(double volume);
		void set_is_playing(bool value);

		Sound* play(size_t id);

		void play();
		void pause();

		void iterate();

		bool load(String^ file);
		bool save(String^ name);

		int pos() { return _pos; }

		Sound* operator[](int i)
		{
			return &_sounds[i];
		}

	public:
		delegate void callback_play(); // called everytime a sound is played
		delegate void callback_done(); // called when reached end

		callback_play^ _callback_play;
		callback_done^ _callback_done;

	private:
		void player_loop();

		bool load_wav(String^ file);
		bool load_txt(String^ file);

	private:
		size_t _pos, _size;
		bool _is_playing, _shutdown;
		double _volume;

		Sound* _sounds;
		Sound* _sound;

		Thread^ _thread;
	};
}

