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

#include "Interpretable.h"

#include "SoundData.h"
#include "SoundGene.h"

namespace IESFX
{
	class Interpreter
	{
	public:
		Interpreter();
		~Interpreter() = default;

		void read_file(Interpretable* ptr, const std::string& filename);
		void read_str(Interpretable* ptr, const std::string& str);

		void clear();

	private:
		void tokenize(std::queue<std::string>& lines);

		template<class T>
		T* cast()
		{
			return dynamic_cast<T*>(_ptr);
		}

	private:
		void evaluate(const std::vector<std::string>& tokens);

		std::string peek();
		std::string peek(int steps);

		void consume(const std::string& token);

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
		size_t _position;
		std::vector<std::string> _tokens;

		std::string _var; // Current evaluated variable that is to be assigned a value
		std::map<std::string, size_t> _variables;

		Interpretable* _ptr;
		SoundData* _data;
		SoundGene* _gene;

		int _line;

	private:
		Interpreter(const Interpreter& rhs) = delete;
		Interpreter& operator=(const Interpreter& rhs) = delete;
	};

}

