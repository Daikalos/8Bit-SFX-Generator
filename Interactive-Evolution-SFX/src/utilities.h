#pragma once

#include <Windows.h>
#include <string>
#include <codecvt>
#include <type_traits>
#include <sstream>

namespace util
{
	template<class T>
	constexpr static double scale(T value, T min, T max)
	{
		return (value - min) / static_cast<double>(max - min);
	}

	template<class T, typename std::enable_if_t<!std::is_pointer_v<T>>>
	static void print(const T& output)
	{
		std::wstring woutput = std::to_wstring(output) + L"\n";
		OutputDebugString(woutput.c_str());
	}
	template<class T>
	static void print(T* output)
	{
		void* address = static_cast<void*>(output);
		std::stringstream ss;
		ss << address;
		dbout(ss.str());
	}

	static void print(const std::wstring& output)
	{
		OutputDebugString((output + L"\n").c_str());
	}
	static void print(const std::string& output)
	{
		print(std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(output + "\n"));
	}

	static void print(const wchar_t* output) { print(std::wstring(output)); }
	static void print(const char* output) { print(std::string(output)); }

	template<class T>
	int size(const T& arr)
	{
		return sizeof(arr) / sizeof(T);
	}
}