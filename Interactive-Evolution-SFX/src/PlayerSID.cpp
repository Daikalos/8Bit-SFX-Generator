#include "PlayerSID.h"

PlayerSID::PlayerSID()
{
	_sid = new RESID::SID();
	_sid->set_chip_model(RESID::chip_model::MOS8580);

}

PlayerSID::~PlayerSID()
{
	delete _sid;
	delete _buffer;
}

void PlayerSID::set_volume(double volume)
{
	_volume = volume;
}
