#include "Tokenizer.hh"
#include <iostream>
#include <string>

Tokenizer::Tokenizer()
{
}

Tokenizer::~Tokenizer()
{
}

const TokensLine *Tokenizer::tokenizeLine(const std::string &line)
{
    TokensLine *tokens = new TokensLine;
    const char *linePtr = line.c_str();
    unsigned int lineIndex = 0;

    // std::cout << line << std::endl;
    while (lineIndex != line.size())
        _fillTokensList(linePtr, lineIndex, tokens);
    if (!_checkTokensLine(tokens))
    {
        for (Token *token : *tokens)
            delete token;
        delete tokens;
        tokens = NULL;
    }
    return tokens;
}

void Tokenizer::_fillTokensList(const char *line, unsigned int &lineIndex, TokensLine *tokens)
{
    Token::eType type = Token::getTokenFromChar(line[lineIndex]);
    Token *token = NULL;

    if (!tokens->empty() && tokens->back()->type() == type)
        token = tokens->back();
    else
    {
        token = new Token;
        tokens->push_back(token);
    }
    token->setType(type);
    token->addChar(line[lineIndex]);
    ++lineIndex;
}

bool Tokenizer::_checkTokensLine(TokensLine *tokens) const
{
    // Make line act as empty if there is only spaces and tabulations
    if (tokens->size() == 1 && tokens->back()->type() == Token::eType::BLANK_SPACE)
    {
        delete tokens->back();
        tokens->pop_back();
        return true;
    }
    for (Token *token : *tokens)
    {
        // std::cout << "Token | type = " << token->type() << " | value ='" << token->raw() << "'" << std::endl;
        if (token->type() == Token::eType::UNKNOWN)
        {
            // std::cerr << "Invalid token \"" << token->raw() << "\"" << std::endl;
            std::cerr << "Invalid token" << std::endl;
            return false;
        }
    }
    // std::cout << std::endl;
    return true;
}
