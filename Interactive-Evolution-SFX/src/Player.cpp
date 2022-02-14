#include "Player.h"

using namespace IESFX;

Player::Player(std::vector<Sound>* sounds)
	: _sounds(sounds), _sound(nullptr), _is_playing(false), _volume(0.325), _pos(0)
{

}

Player::~Player()
{
	delete _sounds;
}

void Player::set_volume(double volume)
{
	_volume = volume;
}

void Player::play()
{
	//_sound.reset();

	//_sound.write(3, 8);
	//_sound.write(2, 0);
	//_sound.write(5, 9);
	//_sound.write(6, 0);
	//_sound.write(4, 65);
	//_sound.write(4, 64);
	//_sound.write(24, 10);

	//_sound.generate_buffer(2);


	_is_playing = true;
}

void Player::pause()
{
	_is_playing = false;
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
