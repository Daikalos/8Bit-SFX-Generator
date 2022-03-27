#define NATIVE_CODE
#include "SoundData.h"

using namespace IESFX;

SoundData::SoundData()
	: _sid(new RESID::SID()), _size(0), _index(0)
{
	_sid->set_chip_model(CHIP_MODEL);

	_sid->enable_filter(true);
	_sid->enable_external_filter(true);
}

SoundData::~SoundData()
{
	delete _sid;
}

std::vector<sf::Int16>& IESFX::SoundData::operator()(const SoundGene& gene)
{
	Interpreter().read_str(this, gene.output());
	_samples.resize(util::get_size(_size), 0);

	for (auto& comm : _commands)
		comm();

	memset(_samples.data(), 0, std::min<size_t>(_samples.size(), 1024LLU));

	return _samples;
}

void SoundData::read_poke(RESID::reg8 offset, RESID::reg8 value)
{
	enqueue(std::bind(&SoundData::poke, this, offset, value));
}
void SoundData::read_sample(size_t size)
{
	enqueue(std::bind(&SoundData::sample, this, size));
	_size += size;
}

void IESFX::SoundData::poke(RESID::reg8 offset, RESID::reg8 value)
{
	_sid->write(offset, value);
}
void SoundData::sample(size_t size)
{
	RESID::cycle_count delta_t = util::get_cycles(util::get_size(size));
	_index += static_cast<size_t>(_sid->clock(delta_t, _samples.data() + _index, util::get_size(size)));
}
