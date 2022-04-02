//  ---------------------------------------------------------------------------
//  This file is part of the 8-Bit SFX Generator
//	Copyright (C) 2022 Tobias Garpenhall <tobiasgarpenhall@gmail.com>
//
//	This program is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	(at your option) any later version.
//	
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//	GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with this program. If not, see <http://www.gnu.org/licenses/>.
//  ---------------------------------------------------------------------------

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
	template<class T>
	static double scale(T value, T min, T max)
	{
		return (value - min) / static_cast<double>(max - min);
	}

#ifdef NATIVE_CODE
	template<class T>
	static double map(T x, T in_min, T in_max, T out_min, T out_max)
	{
		return ((out_max - out_min) / static_cast<double>(in_max - in_min)) * (x - in_min) + out_min;
	}

	template<class T, size_t size>
	static constexpr size_t arr_size(const T(&)[size])
	{
		return size;
	}

	static int get_cycles(size_t size)
	{
		return std::lround((double)IESFX::CLOCK_FREQ / ((double)IESFX::SAMPLE_RATE / size));
	}
	static size_t get_size(size_t size)
	{
		return size * IESFX::CLOCKS_PER_SAMPLE;
	}

	static float time(size_t size)
	{
		return get_size(size) / (float)IESFX::SAMPLE_RATE;
	}

	template<typename T> 
	static T clamp(T val, const T min, const T max)
	{
		val = (val < min) ? min : val;
		val = (val > max) ? max : val;
		return val;
	}

	static thread_local std::mt19937_64 dre(std::chrono::steady_clock::now().time_since_epoch().count());

	template<typename T, typename std::enable_if_t<std::is_floating_point_v<T>>* = nullptr>
	static T random(T min, T max)
	{
		std::uniform_real_distribution<T> uid(min, max);
		return (T)uid(dre);
	}
	template<typename T, typename std::enable_if_t<!std::is_floating_point_v<T>>* = nullptr>
	static T random(T min, T max)
	{
		std::uniform_int_distribution<T> uid(min, max);
		return (T)uid(dre);
	}

	template<typename T, typename std::enable_if_t<std::is_integral_v<T>>* = nullptr>
	static std::vector<T> random(T size)
	{
		std::vector<T> result;
		for (T i = 0; i < size; ++i)
			result.push_back(i);
		std::shuffle(result.begin(), result.end(), dre);

		return result;
	}

	template<typename T, typename... Args, typename std::enable_if_t<std::is_arithmetic_v<T>>* = nullptr>
	static T random_arg(const Args&... args)
	{
		std::vector<T> x { { args... } };
		return x[util::random<size_t>(0, x.size() - 1)];
	}

	static RESID::reg8 ropoke() { return util::random<RESID::reg8>(0, IESFX::POKE_OFFSET); }
	static RESID::reg8 rvpoke() { return util::random<RESID::reg8>(1, IESFX::POKE_VALUE); }
	static size_t rsample() { return util::random(IESFX::MIN_SAMPLE_SIZE, IESFX::MAX_SAMPLE_SIZE); }

	static double random() { return util::random(0.0, 1.0); }
#endif

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