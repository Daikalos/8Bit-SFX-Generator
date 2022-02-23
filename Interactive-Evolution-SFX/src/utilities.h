#pragma once

#if _DEBUG

#include <Windows.h>
#include <codecvt>

#endif

#include <random>
#include <chrono>

#include "Config.h"

namespace util
{
	static std::default_random_engine dre(std::chrono::steady_clock::now().time_since_epoch().count());

	template<class T>
	static double scale(T value, T min, T max)
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

	template<typename T> 
	static T clamp(T val, const T min, const T max)
	{
		val = (val < min) ? min : val;
		val = (val > max) ? max : val;
		return val;
	}

	template<typename T, typename std::enable_if_t<std::is_floating_point_v<T>>* = nullptr>
	static T random(T min, T max)
	{
		std::uniform_real_distribution<> uid(min, max);
		return (T)uid(dre);
	}
	template<typename T, typename std::enable_if_t<!std::is_floating_point_v<T>>* = nullptr>
	static T random(T min, T max)
	{
		std::uniform_int_distribution<> uid(min, max);
		return (T)uid(dre);
	}

#if _DEBUG
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
		print(std::wstring_convert<std::codecvt_utf16<wchar_t>>().from_bytes(output));
	}

	static void print(const wchar_t* output) { print(std::wstring(output)); }
	static void print(const char* output) { print(std::string(output)); }
#endif
}