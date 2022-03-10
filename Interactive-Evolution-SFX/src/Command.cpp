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
std::shared_ptr<Command> Poke::clone() const
{
	return std::make_shared<Poke>(*this);
}
std::shared_ptr<Command> Poke::flip() const
{
	return std::make_shared<Sample>(Sample(util::rsample()));
}

Sample::Sample(size_t s)
	: size(s) { }

std::string Sample::print() const
{
	return std::string("sample " + std::to_string(size));
}
std::shared_ptr<Command> Sample::clone() const
{
	return std::make_shared<Sample>(*this);
}
std::shared_ptr<Command> Sample::flip() const
{
	return std::make_shared<Poke>(Poke(util::ropoke(), util::rvpoke()));
}
