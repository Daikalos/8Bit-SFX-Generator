#pragma once

namespace IESFX
{
	class Interpretable
	{
	public:
		Interpretable() { }
		virtual ~Interpretable() { }

	protected:
		virtual void read_poke(unsigned int offset, unsigned int value) = 0;
		virtual void read_sample(size_t size) = 0;

	private:
		friend class Interpreter;
	};
}