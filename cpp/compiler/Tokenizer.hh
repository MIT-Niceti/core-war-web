#ifndef     TOKENIZER_HH_
# define    TOKENIZER_HH_

# include <vector>
# include <string>

class Tokenizer
{
public:
    class Token;

    Tokenizer();
    ~Tokenizer();
    std::vector<Token> *tokenizeLine(const std::string &line);

private:
    void _fillTokensList(const char *, int &, std::vector<Token> *&);
};

# include "Token.hh"

#endif      // !TOKENIZER_HH_
