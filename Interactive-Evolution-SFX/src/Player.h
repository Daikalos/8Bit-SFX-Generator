#pragma once

#include <iostream>
#include <vector>

#include <fstream>

#include "utilities.h"
#include "Config.h"
#include "Sound.h"

#include <SFML/Audio.hpp>

class Player
{
public:
	Player();
	~Player();

	void set_volume(double volume);

	void play();
	void pause();

	bool load(const std::string& file);

private:
	Sound _sound;
};

