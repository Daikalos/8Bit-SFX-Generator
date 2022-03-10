#pragma once

#include <resid/siddefs.h>
#include <string>
#include <memory>

#include "Utilities.h"

struct Command
{
	Command() { }
	virtual ~Command() { }

	virtual std::string print() const = 0;
	virtual std::shared_ptr<Command> clone() const = 0;
	virtual std::shared_ptr<Command> flip() const = 0;
};

struct Poke : public Command
{
	Poke(RESID::reg8 o, RESID::reg8 v);

	std::string print() const override;
	std::shared_ptr<Command> clone() const override;
	std::shared_ptr<Command> flip() const override;

	RESID::reg8 offset{0}, value{0};
};

struct Sample : public Command
{
	Sample(size_t s);

	std::string print() const override;
	std::shared_ptr<Command> clone() const override;
	std::shared_ptr<Command> flip() const override;

	size_t size{0};
};

