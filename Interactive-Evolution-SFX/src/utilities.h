#pragma once

namespace util
{
	template<class T>
	constexpr static double scale(T value, T min, T max)
	{
		return (value - min) / static_cast<double>(max - min);
	}
}