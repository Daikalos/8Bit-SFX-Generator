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

#include "Interpreter.h"

using namespace IESFX;

void Interpreter::clear()
{
    _variables.clear();
    _ptr = nullptr;
}

void Interpreter::evaluate(std::vector<std::string>& tokens)
{
    _tokens = std::move(tokens);
    _position = 0;

    parse_Stmt();
}

std::string Interpreter::peek(const int steps)
{
    if (_position + steps >= _tokens.size())
        return "\u0003"; // End of text

    if (_position - steps < 0)
        throw std::out_of_range(std::to_string(steps) + " is out of range");

    return _tokens[_position + steps];
}

void Interpreter::consume(const std::string_view& token)
{
    std::string next_token = peek();

    if (next_token.empty())
        throw std::runtime_error("Consumed past last token");
    if (next_token != token)
        throw std::runtime_error("Could not consume token '" + std::string(token) + "'");

    ++_position;
}

void Interpreter::parse_Stmt()
{
    const std::string next_token = peek();
    if (is_variable(next_token))
    {
        consume(next_token);
        if (peek() == "=")
        {
            _var = next_token;

            consume("=");
            parse_AssgStmt();
        }
        else if (next_token == "poke")
            parse_PokeStmt();
        else if (next_token == "sample")
            parse_SampleStmt();
        else
            throw std::runtime_error("'" + next_token + " is not a valid statement; expected: 'poke' or 'sample'");
    }
    else
        throw std::runtime_error("syntax error");
}
void Interpreter::parse_AssgStmt()
{
    if (_var.empty())
        throw std::runtime_error("variable name is undefined");

    _variables[_var] = parse_MathExp();
}
void Interpreter::parse_PokeStmt()
{
    unsigned int offset = 0;
    {
        const std::string next_token = peek();
        consume(next_token);

        if (is_integer(next_token))
            offset = std::stoi(next_token);
        else
            throw std::runtime_error("the given expression: '" + next_token + "' is not valid");
    }

    unsigned int value = 0;
    {
        const std::string next_token = peek();
        consume(next_token);

        if (is_integer(next_token))
            value = std::stoi(next_token);
        else
            throw std::runtime_error("the given expression: '" + next_token + "' is not valid");
    }

    _ptr->read_poke(offset, value);
}
void Interpreter::parse_SampleStmt()
{
    const std::string next_token = peek();
    consume(next_token);

    if (is_integer(next_token))
    {
       std::size_t size = std::stoi(next_token);
        _ptr->read_sample(size);
    }
    else
        throw std::runtime_error("the given expression: '" + next_token + "' is not valid");
}

int Interpreter::parse_MathExp()
{
    return parse_SumExp();
}
int Interpreter::parse_SumExp()
{
    int val = parse_ProductExp();

    std::string next_token = peek();
    while (true)
    {
        if (next_token == "+")
        {
            consume("+");
            val += parse_ProductExp();
        }
        else if (next_token == "-")
        {
            consume("-");
            val -= parse_ProductExp();
        }
        else
            break;

        next_token = peek();
    }

    return val;
}
int Interpreter::parse_ProductExp()
{
    int val = parse_PrimaryExp();

    std::string next_token = peek();
    while (true)
    {
        if (next_token == "*")
        {
            consume("*");
            val *= parse_PrimaryExp();
        }
        else if (next_token == "/")
        {
            consume("/");
            val /= parse_PrimaryExp();
        }
        else
            break;

        next_token = peek();
    }

    return val;
}
int Interpreter::parse_PrimaryExp()
{
    int val = 0;
    std::string next_token = peek();

    if (is_integer(next_token))
    {
        consume(next_token);
        val = std::stoi(next_token);
    }
    else if (is_variable(next_token))
    {
        consume(next_token);
        val = get_variable(next_token);
    }
    else if (next_token == "(")
    {
        consume("(");

        val = parse_MathExp();

        if (peek() == ")")
            consume(")");
        else
            throw std::runtime_error("no enclosing paranthesis found");
    }
    else
        throw std::runtime_error("the given expression: '" + next_token + "' is not valid");

    return val;
}

bool Interpreter::is_integer(const std::string& token)
{
    return std::regex_match(token, std::regex("-?[0-9]+"));
}
bool Interpreter::is_variable(const std::string& token)
{
    return std::regex_match(token, std::regex("[a-zA-z][a-zA-z0-9]*"));
}

int Interpreter::get_variable(const std::string& name)
{
    auto it = _variables.find(name);

    if (it != _variables.end())
        return it->second;
    else
        throw std::runtime_error("variable '" + name + "' is not defined");
}

void Interpreter::tokenize(std::queue<std::string>& lines)
{
    while (!lines.empty())
    {
        std::vector<std::string> tokens;

        std::string line = lines.front();
        std::string stmt;

        stmt.reserve(line.size());
        for (const char& c : line)
        {
            if (c == ' ')
            {
                if (!stmt.empty())
                {
                    tokens.push_back(stmt);
                    stmt.clear();
                }
            }
            else
                stmt += c;
        }

        if (!stmt.empty())
            tokens.push_back(stmt);

        if (!tokens.empty() && tokens.front() != "//")
            evaluate(tokens);

        lines.pop();
    }
}

void Interpreter::read_file(Interpretable* ptr, const std::string& filename)
{
    clear();

    _ptr = ptr;

    std::queue<std::string> lines;

    std::string line;
    std::ifstream file(filename);
    if (file.is_open())
    {
        while (file.good())
        {
            getline(file, line);
            lines.push(line);
        }
        file.close();
    }
    else
        throw std::runtime_error("unable to open file");

    tokenize(lines);
}
void Interpreter::read_str(Interpretable* ptr, const std::string& str)
{
    clear();

    _ptr = ptr;

    std::queue<std::string> lines;

    std::string line;
    std::stringstream ss(str);
    while (ss.good())
    {
        getline(ss, line, '\n');
        lines.push(line);
    }

    tokenize(lines);
}
