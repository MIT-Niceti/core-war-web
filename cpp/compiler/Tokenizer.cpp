#include "Tokenizer.hh"
#include <string>
#include <iostream>

Tokenizer::Tokenizer()
{
}

Tokenizer::~Tokenizer()
{
}

std::vector<Tokenizer::Token> *Tokenizer::tokenizeLine(const std::string &line)
{
    std::vector<Token> *tokens = new std::vector<Token>;
    const char *linePtr = line.c_str();
    int lineIndex = 0;

    std::cout << line << std::endl;
    while (linePtr[lineIndex] != '\0')
        _fillTokensList(linePtr, lineIndex, tokens);
    return tokens;
}

void Tokenizer::_fillTokensList(const char *line, int &lineIndex, std::vector<Token> *&tokens)
{
    int i = 0;

    while (i != Token::eType::UNKNOWN && Token::all[i].find(line[lineIndex]) == std::string::npos)
        ++i;
    if (i != Token::eType::UNKNOWN)
    {
        if (tokens->empty())
            tokens->push_back(Token());
        if (tokens->back().type != Token::eType::UNKNOWN && tokens->back().type != static_cast<Token::eType>(i))
            tokens->push_back(Token());
        tokens->back().type = static_cast<Token::eType>(i);
        tokens->back().raw.push_back(line[lineIndex]);
        // std::cout << static_cast<Token::eType>(i) << std::endl;
    }
    else
    {
        std::cerr << "Invalid token" << std::endl;
    }
    ++lineIndex;
}
