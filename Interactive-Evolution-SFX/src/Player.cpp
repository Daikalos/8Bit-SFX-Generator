#include "Player.h"

using namespace IESFX;

Player::Player(std::vector<Sound>* sounds)
	: _sounds(sounds), _sound(nullptr), _is_playing(false), _shutdown(false), _volume(0.325), _pos(0), _thread(nullptr)
{
	_thread = gcnew Thread(gcnew ThreadStart(this, &Player::player_loop));
	_thread->Start();
}

Player::~Player()
{
	delete _sounds;
	_shutdown = true;
}

void Player::reset()
{
	_pos = 0;
	_is_playing = false;
}

void Player::set_volume(double volume)
{
	_volume = volume;
}

void Player::play()
{
	if (_is_playing)
		return;

	_callback_play();
	(_sound = &_sounds->at(_pos))->play();
	_is_playing = true;

	//_sound.reset();

	//_sound.write(3, 8);
	//_sound.write(2, 0);
	//_sound.write(5, 9);
	//_sound.write(6, 0);
	//_sound.write(4, 65);
	//_sound.write(4, 64);
	//_sound.write(24, 10);

	//_sound.generate_buffer(2);
}

void Player::pause()
{
	if (!_is_playing && _sound != nullptr)
		return;

	_sound->pause();
	_is_playing = false;
}

void Player::iterate()
{
	if (_pos >= _sounds->size() - 1)
	{
		_callback_done();
		_pos = _is_playing = false;
	}
	else
	{
		(_sound = &_sounds->at(++_pos))->play();
		_callback_play();
	}
}

void Player::play_sound(const Sound& sound)
{
	
}

bool Player::load(const std::string& file)
{
	_is_playing = false;

	std::ifstream stream(file, std::ios::binary);

	if (stream.is_open())
	{
		std::istream_iterator<char> start(stream), end;
		std::vector<sf::Int16> buffer(start, end);

		

		stream.close();
	}

	return true;
}

bool Player::save(const std::string& name)
{

	return false;
}

void Player::player_loop()
{
	while (!_shutdown)
	{
		if (!_is_playing || _sound == nullptr)
			continue;

		if (_sound->status() == sf::SoundSource::Status::Stopped)
			iterate();
	}
}
