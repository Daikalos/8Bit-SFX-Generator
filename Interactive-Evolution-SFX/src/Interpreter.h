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

#include "SoundInfo.h"

namespace IESFX
{
	class Interpreter
	{
	public:
		Interpreter();
		~Interpreter() = default;

		void read_file(SoundInfo& sound, const std::string& filename);
		void read_str(SoundInfo& sound, const std::string& str);

		void clear();

	private:
		void tokenize(std::queue<std::string>& lines);

	private:
		void evaluate(const std::vector<std::string>& tokens);

		std::string peek();
		std::string peek(int steps);

		void consume(const std::string& token);

		void parse_Stmt();
		void parse_AssgStmt();
		void parse_PokeStmt();
		void parse_ForStmt();
		void parse_NextStmt();

		int parse_MathExp();
		int parse_SumExp();
		int parse_ProductExp();
		int parse_PrimaryExp();

		bool is_integer(const std::string& token);
		bool is_variable(const std::string& token);

		int get_variable(const std::string& name);

	private:
		size_t _position;
		std::vector<std::string> _tokens;

		std::string var_name; // Current evaluated variable that is to be assigned a value
		std::map<std::string, int> variables;

		SoundInfo* _sound;

	private:
		Interpreter(const Interpreter& rhs) = delete;
		Interpreter& operator=(const Interpreter& rhs) = delete;
	};

}

