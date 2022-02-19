#include "Interpreter.h"

using namespace IESFX;

Interpreter::Interpreter()
{

}

void Interpreter::clear()
{

}

void Interpreter::evaluate(const std::vector<std::string>& tokens)
{
    _tokens = tokens;
    _position = 0;

    try
    {
        parse_Stmt();
    }
    catch (std::exception exception)
    {
        std::cout << exception.what();
    }
}

std::string Interpreter::peek()
{
    return peek(0);
}

std::string Interpreter::peek(int steps)
{
    if (_position + steps >= _tokens.size())
        return "\u0003"; // End of text

    if (_position - steps < 0)
        throw std::out_of_range(std::to_string(steps) + " is out of range");

    return _tokens[_position + steps];
}

void Interpreter::consume(const std::string& token)
{
    std::string next_token = peek();

    if (next_token.empty())
        throw std::runtime_error("Consumed past last token");
    if (next_token != token)
        throw std::runtime_error("Could not consume token '" + token + "'");

    ++_position;
}

void Interpreter::parse_Stmt()
{
    std::string next_token = peek();
    if (is_variable(next_token))
    {
        consume(next_token);
        if (peek() == "=")
        {
            var_name = next_token;

            consume("=");
            parse_AssgStmt();
        }
        else if (next_token == "pokes")
            parse_PokesStmt();
        else if (next_token == "for")
            parse_ForStmt();
        else if (next_token == "next")
            parse_NextStmt();
        else
            throw std::runtime_error("'" + next_token + " is not a valid statement; expected: 'pokes', 'for', '=' or 'next'");
    }
    else
        throw std::runtime_error("syntax error");
}
void Interpreter::parse_AssgStmt()
{
    if (var_name.empty())
        throw std::runtime_error("variable name is undefined");

    variables[var_name] = parse_MathExp();
}
void Interpreter::parse_PokesStmt()
{

}
void Interpreter::parse_ForStmt()
{

}
void Interpreter::parse_NextStmt()
{

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
    if (variables.find(name) != variables.end())
        return variables[name];
    else
        throw std::runtime_error("variable '" + name + "' is not defined");
}

void Interpreter::tokenize(std::queue<std::string>& codelines)
{
    while (!codelines.empty())
    {
        std::vector<std::string> tokens;

        std::string line = codelines.front();
        std::string stmt = std::string();

        for (const char& c : line)
        {
            if (c == ' ')
            {
                if (!stmt.empty())
                {
                    tokens.push_back(stmt);
                    stmt = std::string();
                }
            }
            else
                stmt += c;
        }

        if (!stmt.empty())
            tokens.push_back(stmt);

        if (!tokens.empty())
            evaluate(tokens);

        codelines.pop();
    }
}

void Interpreter::read_file(const std::string& filename)
{
    std::queue<std::string> codeLines;

    std::string line;
    std::ifstream file(filename);
    if (file.is_open())
    {
        while (file.good())
        {
            getline(file, line);
            codeLines.push(line);
        }
        file.close();
    }
    else
        throw std::runtime_error("unable to open file");

    tokenize(codeLines);
}
