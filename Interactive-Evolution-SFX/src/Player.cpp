#include "Player.h"

using namespace IESFX;

Player::Player(Evolution* evolution, size_t size, double volume)
	: _evolution(evolution), _position(0), _size(size), _is_playing(false), 
	_shutdown(false), _volume(volume), _sounds(nullptr), _sound(nullptr), _thread(nullptr)
{
	_thread = gcnew Thread(gcnew ThreadStart(this, &Player::player_loop));
	_thread->IsBackground = true;
	_thread->Start();

	_sounds = new Sound[size];
}

Player::~Player()
{
	delete[] _sounds;
	_shutdown = true;
}

void Player::initialize()
{
	std::vector<SoundGene> infos;

	for (int i = 0; i < _size; ++i)
	{
		SoundGene info;

		//for (int j = 0; j < 24; ++j)
		//	info[j] = rand() % 80;

		//info[24] = 13;

		infos.push_back(info);
	}

	update(infos);
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

void Player::set_volume(double volume)
{
	_volume = volume;

	if (_sound != nullptr)
		_sound->set_volume(_volume);
}
void Player::set_is_playing(bool value)
{
	if (value && _is_playing)
		return;

	initialize();

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

void Player::iterate()
{
	(++_position >= _size) ? reset() : play();
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

void Player::update(const std::vector<SoundGene>& info)
{
	for (int i = 0; i < info.size(); ++i)
		_sounds[i].create_buffer(info.at(i));

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
