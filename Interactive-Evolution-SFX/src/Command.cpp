#include "Command.h"

using namespace IESFX;

Poke::Poke(RESID::reg8 o, RESID::reg8 v)
	: offset(o), value(v) { }

std::string Poke::print() const
{
	return std::string("poke " +
		std::to_string(offset) + " " +
		std::to_string(value));
}
std::unique_ptr<Command> Poke::clone() const
{
	return std::make_unique<Poke>(*this);
}
std::unique_ptr<Command> Poke::flip() const
{
	return std::make_unique<Sample>(Sample(util::rsample()));
}
bool Poke::equal_to(const Command* rhs) const
{
	const Poke* poke = dynamic_cast<const Poke*>(rhs);

	if (poke == nullptr)
		return false;

	return this->offset == poke->offset && this->value == poke->value;
}

Sample::Sample(size_t s)
	: size(s) { }

std::string Sample::print() const
{
	return std::string("sample " + std::to_string(size));
}
std::unique_ptr<Command> Sample::clone() const
{
	return std::make_unique<Sample>(*this);
}
std::unique_ptr<Command> Sample::flip() const
{
	return std::make_unique<Poke>(Poke(util::ropoke(), util::rvpoke()));
}
bool Sample::equal_to(const Command* rhs) const
{
	const Sample* sample = dynamic_cast<const Sample*>(rhs);

	if (sample == nullptr)
		return false;

	return this->size == sample->size;
}
