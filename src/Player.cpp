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

#include "Player.h"

using namespace IESFX;

Player::Player(Evolution* evolution, std::size_t size, float volume)
	: _size(size), _volume(volume), _evolution(evolution)
{
	_thread = gcnew Thread(gcnew ThreadStart(this, &Player::player_loop));
	_thread->Name = "player_thread";
	_thread->IsBackground = true;
	_thread->Start();

	_object = gcnew Object();

	_sounds = new Sound[size];
}

Player::~Player()
{
	delete[] _sounds;
}

Sound* Player::operator[](std::size_t i)
{
	return &_sounds[i];
}

std::size_t Player::position() 
{ 
	return _position;
}
bool Player::active() 
{ 
	return _is_playing; 
}

void Player::set_volume(float volume)
{
	if (volume == _volume)
		return;

	_volume = volume;

	for (int i = 0; i < _size; ++i)
		_sounds[i].set_volume(_volume);
}
void Player::set_active(bool value)
{
	if (value && _is_playing)
		return;

	value ? play() : pause();
	_is_playing = value;
}

void Player::shutdown()
{
	Monitor::Enter(_object);
	try		
	{ 
		_shutdown = true;
		Monitor::Pulse(_object); 
	}
	finally { Monitor::Exit(_object); }

	_thread->Join();
}

void Player::iterate()
{
	Monitor::Enter(_object);
	try		{ Monitor::Pulse(_object); }
	finally { Monitor::Exit(_object); }

	_iterate = true;
}

void Player::reset()
{
	_callback_done();

	_is_playing = false;
	_position = 0;

	if (_sound != nullptr)
		_sound->stop();

	_sound = nullptr;
}

Sound* Player::play(std::size_t id)
{
	Sound* sound = &_sounds[id];

	sound->set_volume(_volume);
	sound->play();

	return sound;
}

void Player::play()
{
	_callback_play();
	_sound = play(_position);
}
void Player::pause()
{
	if (_is_playing)
		_sound->pause();
}

void Player::update(const std::vector<const SoundGene*>& genes)
{
	for (int i = 0; i < genes.size(); ++i)
		_sounds[i].create_buffer(*genes[i]);

	_callback_update(_sounds);
}

void Player::player_loop()
{
	while (!_shutdown)
	{
		if (!_is_playing || _sound == nullptr)
			continue;
		
		if (_sound->status() == sf::SoundSource::Status::Stopped || _iterate)
		{
			if (_iterate)
				_sound->stop();

			if (++_position < _size)
			{
				if (!_iterate)
				{
					Monitor::Enter(_object);
					try
					{
						if (_shutdown) break;
						Monitor::Wait(_object, TimeSpan::FromSeconds(0.5));
						if (_shutdown) break;
					}
					finally { Monitor::Exit(_object); }

					if (!_is_playing)
						continue;
				}
				
				play();
			}
			else
				reset();

			_iterate = false;
		}
	}
}
