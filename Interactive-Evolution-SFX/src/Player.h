//  ---------------------------------------------------------------------------
//  This file is part of the 8-Bit SFX Generator
//	Copyright (C) 2022 Tobias Garpenhall <tobiasgarpenhall@gmail.com>
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
#include "Interpreter.h"

namespace IESFX
{
	using namespace System;
	using namespace System::Threading;
	using namespace System::IO;

	public ref class Player
	{
	public:
		Player(Evolution* evolution, size_t size, float volume);
		~Player();

		void shutdown();
		void iterate();

		bool is_playing() { return _is_playing; }

		void reset();

		void set_volume(float volume);
		void set_is_playing(bool value);

		Sound* play(size_t id);

		void play();
		void pause();

		void update(std::vector<SoundGene>& genes);

		size_t position() { return _position; }
		bool active() { return _is_playing; }

		Sound* operator[](size_t i)
		{
			return &_sounds[i];
		}

	public:
		delegate void callback_play(); // called everytime a sound is played
		delegate void callback_done(); // called when reached end
		delegate void callback_update(Sound*);

		callback_play^ _callback_play;
		callback_done^ _callback_done;
		callback_update^ _callback_update;

	private:
		void player_loop();

	private:
		size_t 
			_position{0}, 
			_size;
		bool 
			_is_playing{false}, 
			_shutdown{false},
			_iterate{false};
		float 
			_volume{0.0};

		Evolution* 
			_evolution;
		Sound
			*_sounds{nullptr},
			*_sound{nullptr};

		Thread^ _thread;
		Object^ _object;
	};
}

