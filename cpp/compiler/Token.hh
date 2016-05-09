#ifndef		TOKEN_HH_
# define	TOKEN_HH_

# include <vector>
# include <string>

typedef std::vector<std::string> TokensDefinition;

class Token
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
        UNKNOWN = 10
    };

private:
    static const TokensDefinition _all;

    eType _type;
    std::string *_raw;

public:
    Token();
    ~Token();

    static eType getTokenFromChar(char);

    const std::string &raw() const;
    eType type() const;

    void addChar(char);
    void setType(eType);
};

#endif		// !TOKEN_HH_
