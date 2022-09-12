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

#include <iostream>
#include <fstream>
#include <functional>
#include <limits>
#include <queue>
#include <vector>
#include <string>
#include <regex>
#include <map>
#include <sstream>
#include <string_view>

#include "Interpretable.h"

namespace IESFX
{
	class Interpreter final
	{
	public:
		Interpreter() = default;
		~Interpreter() = default;

		void read_file(Interpretable* ptr, const std::string& filename);
		void read_str(Interpretable* ptr, const std::string& str);

		void clear();

		template<class T, typename std::enable_if_t<std::is_base_of_v<Interpretable, T>>* = nullptr>
		std::vector<T> read_file(const std::string& filename);

	private:
		void tokenize(std::queue<std::string>& lines);

	private:
		void evaluate(std::vector<std::string>& tokens);

		std::string peek(const int steps = 0);

		void consume(const std::string_view& token);

		void parse_Stmt();
		void parse_AssgStmt();
		void parse_PokeStmt();
		void parse_SampleStmt();

		int parse_MathExp();
		int parse_SumExp();
		int parse_ProductExp();
		int parse_PrimaryExp();

		bool is_integer(const std::string& token);
		bool is_variable(const std::string& token);

		int get_variable(const std::string& name);

	private:
		size_t _position{0};
		std::vector<std::string> _tokens;

		std::string _var; // Current evaluated variable that is to be assigned a value
		std::unordered_map<std::string, int> _variables;

		Interpretable* _ptr{nullptr};

	private:
		Interpreter(const Interpreter& rhs) = delete;
		Interpreter& operator=(const Interpreter& rhs) = delete;
	};

	template<class T, typename std::enable_if_t<std::is_base_of_v<Interpretable, T>>*>
	std::vector<T> Interpreter::read_file(const std::string& filename)
	{
		clear();

		std::vector<T> result;
		std::queue<std::string> lines;

		std::string line;
		std::ifstream file(filename);
		if (file.is_open())
		{
			while (file.good())
			{
				getline(file, line);
				if (line != "RUN")
					lines.push(line);
				else
				{
					result.push_back(T());
					_ptr = &result[result.size() - 1];

					tokenize(lines);

					std::queue<std::string>().swap(lines);
				}
			}
			file.close();
		}
		else
			throw std::runtime_error("unable to open file");

		return result;
	}
}

