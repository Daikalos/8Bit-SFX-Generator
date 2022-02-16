#include "Player.h"

using namespace IESFX;

Player::Player(size_t size)
	: _sounds(new std::vector<Sound>(size)), _sound(nullptr), _is_playing(false), _shutdown(false), _volume(0.325), _pos(0), _thread(nullptr)
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
	_callback_done();

	_pos = 0;
	_is_playing = false;
	_sound = nullptr;
}

void Player::set_volume(double volume)
{
	_volume = volume;
}

void Player::play()
{
	if (_is_playing)
		return;

	_is_playing = true;
	_sound = this[_pos];

	_callback_play();

	_sound->play();

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
	(++_pos >= _sounds->size()) ? reset() : play();
}

bool Player::load(String^ file)
{
	String^ ext = Path::GetExtension(file)->ToLower();

	_is_playing = false;

	if (ext->Equals(".txt"))
		return load_txt(file);
	if (ext->Equals(".wav"))
		return load_wav(file);

	return false;
}

bool Player::save(String^ name)
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

bool Player::load_wav(String^ file)
{
	std::string filename = msclr::interop::marshal_as<std::string>(file);

	std::ifstream stream(filename, std::ios::binary);

	if (stream.is_open())
	{
		std::istream_iterator<char> start(stream), end;
		std::vector<sf::Int16> buffer(start, end);



		stream.close();
	}

	return true;
}

bool Player::load_txt(String^ file)
{


	return true;
}
