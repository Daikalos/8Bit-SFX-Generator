#pragma once

#include <Windows.h>
#include <string>
#include <codecvt>
#include <type_traits>
#include <sstream>

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
		return static_cast<double>(IESFX::CLOCK_FREQ) / (static_cast<double>(IESFX::SAMPLE_RATE) / size);
	}

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
}