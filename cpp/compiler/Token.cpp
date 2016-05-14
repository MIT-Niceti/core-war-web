#include "Token.hh"

const TokensDefinition Token::_all = {
    "0123456789",
    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ",
    "-_",
    " \t",
    "\"",
    ".",
    ":",
    "%",
    ",",
    "#"
};

Token::Token()
    : _type(eType::UNKNOWN), _raw(NULL)
{
    _raw = new std::string;
}

Token::~Token()
{
    delete _raw;
}

Token::eType Token::getTokenFromChar(char c)
{
    int i = 0;

    while (i != eType::UNKNOWN && _all[i].find(c) == std::string::npos)
        ++i;
    return static_cast<eType>(i);
}

const std::string &Token::raw() const
{
    return *_raw;
}

Token::eType Token::type() const
{
    return _type;
}

void Token::addChar(char c)
{
    _raw->push_back(c);
}

void Token::setType(eType type)
{
    _type = type;
}
