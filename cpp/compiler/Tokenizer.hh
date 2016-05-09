#ifndef     TOKENIZER_HH_
# define    TOKENIZER_HH_

# include "Token.hh"
# include <vector>
# include <string>

typedef std::vector<Token *> TokensLine;
typedef std::vector<const TokensLine *> TokensLines;

class Tokenizer
{
public:
    Tokenizer();
    ~Tokenizer();
    const TokensLine *tokenizeLine(const std::string &);

private:
    void _fillTokensList(const char *, unsigned int &, TokensLine *);
    bool _checkTokensLine(const TokensLine *) const;
};

#endif      // !TOKENIZER_HH_
