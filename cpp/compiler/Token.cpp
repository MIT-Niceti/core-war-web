#include "Token.hh"

const std::vector<std::string> Tokenizer::Token::all = {
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

Tokenizer::Token::Token()
    : type(eType::UNKNOWN)
{
}

Tokenizer::Token::~Token()
{
}
