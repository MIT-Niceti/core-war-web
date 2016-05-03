#ifndef		TOKEN_HH_
# define	TOKEN_HH_

# include "Tokenizer.hh"
# include <vector>
# include <string>

class Tokenizer::Token
{
public:
    enum eType : int
    {
        DIGITS = 0,
        ALPHABET = 1,
        WORD_SEPARATORS = 2,
        BLANK_SPACE = 3,
        DOUBLE_QUOTES = 4,
        META = 5,
        LABEL = 6,
        DIRECT = 7,
        PARAMETER_SEPARATOR = 8,
        COMMENT = 9,
        UNKNOWN
    };

    static const std::vector<std::string> all;

    eType type;
    std::string raw;

public:
    Token();
    ~Token();
};

#endif		// !TOKEN_HH_
