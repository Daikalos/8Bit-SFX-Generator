#include "Player.h"

using namespace IESFX;

Player::Player(Evolution* evolution, size_t size, double volume)
	: _size(size), _volume(volume), _evolution(evolution)
{
	_thread = gcnew Thread(gcnew ThreadStart(this, &Player::player_loop));
	_thread->IsBackground = true;
	_thread->Start();

	_object = gcnew Object();

	_sounds = new Sound[size];
}

Player::~Player()
{
	delete[] _sounds;
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

void Player::set_volume(float volume)
{
	if (volume == _volume)
		return;

	_volume = volume;

	for (int i = 0; i < _size; ++i)
		_sounds[i].set_volume(_volume);
}
void Player::set_is_playing(bool value)
{
	if (value && _is_playing)
		return;

	value ? play() : pause();
	_is_playing = value;
}

Sound* Player::play(size_t id)
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

bool Player::iterate()
{
	return ++_position < _size;
}

void Player::update(std::vector<SoundGene>& genes)
{
	for (int i = 0; i < genes.size(); ++i)
		_sounds[i].create_buffer(genes[i]);

	for (int i = 0; i < _size; ++i)
		_callback_update(&_sounds[i], i);
}

void Player::player_loop()
{
	while (!_shutdown)
	{
		if (!_is_playing || _sound == nullptr)
			continue;
		
		if (_sound->status() == sf::SoundSource::Status::Stopped)
		{
			if (iterate())
			{
				Monitor::Enter(_object);
				try
				{
					if (_shutdown) break;
					Monitor::Wait(_object, TimeSpan::FromSeconds(0.25));
					if (_shutdown) break;

					play();
				}
				finally { Monitor::Exit(_object); }
			}
			else
				reset();
		}
	}
}

//bool Player::load_wav(String^ file)
//{
//	std::string filename = msclr::interop::marshal_as<std::string>(file);
//
//	std::ifstream stream(filename, std::ios::binary);
//
//	if (stream.is_open())
//	{
//		std::istream_iterator<char> start(stream), end;
//		std::vector<sf::Int16> buffer(start, end);
//
//
//
//		stream.close();
//	}
//
//	return true;
//}
