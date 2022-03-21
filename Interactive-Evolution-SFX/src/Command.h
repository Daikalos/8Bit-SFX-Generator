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
	virtual std::unique_ptr<Command> clone() const = 0;
	virtual std::unique_ptr<Command> flip() const = 0;

	virtual bool equal_to(const Command* rhs) const = 0;

	bool operator==(const Command* rhs) const { return equal_to(rhs); }
	bool operator!=(const Command* rhs) const { return !equal_to(rhs); }
};

struct Poke : public Command
{
	Poke(RESID::reg8 o, RESID::reg8 v);

	std::string print() const override;
	std::unique_ptr<Command> clone() const override;
	std::unique_ptr<Command> flip() const override;

	bool equal_to(const Command* rhs) const override;

	RESID::reg8 offset{0}, value{0};
};

struct Sample : public Command
{
	Sample(size_t s);

	std::string print() const override;
	std::unique_ptr<Command> clone() const override;
	std::unique_ptr<Command> flip() const override;

	bool equal_to(const Command* rhs) const override;

	size_t size{0};
};

