#include "Player.h"

Player::Player()
{
	set_volume(0.325);
}

Player::~Player()
{
	_sound.stop();
}

void Player::set_volume(double volume)
{
	_sound.set_volume(volume);
}

void Player::play()
{
	if (_sound.status() == sf::SoundSource::Playing)
		_sound.stop();

	_sound.reset();

	_sound.write(3, 8);
	_sound.write(2, 0);
	_sound.write(5, 9);
	_sound.write(6, 0);
	_sound.write(4, 65);
	_sound.write(4, 64);
	_sound.write(24, 10);

	_sound.create_buffer(2);

	_sound.play();
}

void Player::pause()
{
	_sound.pause();
}

bool Player::load(const std::string& file)
{
	pause();

	std::ifstream stream(file, std::ios::binary);

	if (stream.is_open())
	{


		stream.close();
	}

	return true;
}
