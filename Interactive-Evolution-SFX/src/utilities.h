#pragma once

#if !NDEBUG

#include <Windows.h>
#include <codecvt>

#endif

#include "Config.h"

namespace util
{
	template<class T>
	constexpr static double scale(T value, T min, T max)
	{
		return (value - min) / static_cast<double>(max - min);
	}

	template<class T>
	static int size(const T& arr)
	{
		return sizeof(arr) / sizeof(T);
	}

	static int get_cycles(size_t size)
	{
		return round((double)IESFX::CLOCK_FREQ / ((double)IESFX::SAMPLE_RATE / size));
	}
	static size_t get_size(size_t size)
	{
		return size * IESFX::CLOCKS_PER_SAMPLE;
	}

#if !NDEBUG
	template<class T>
	static void print(const T& output)
	{
		std::wstring woutput = std::to_wstring(output);
		OutputDebugString(woutput.c_str());
	}

	static void print(const std::wstring& output)
	{
		OutputDebugString(output.c_str());
	}
	static void print(const std::string& output)
	{
		print(std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(output));
	}

	static void print(const wchar_t* output) { print(std::wstring(output)); }
	static void print(const char* output) { print(std::string(output)); }
#endif
}