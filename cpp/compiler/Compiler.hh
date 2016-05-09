#ifndef		COMPILER_HH_
# define	COMPILER_HH_

# include "Tokenizer.hh"
# include <vector>
# include <string>

class		Compiler
{
private:
    const std::string _inputFile;
    TokensLines _tokenizedFile;

public:
    Compiler(const std::string &);
    ~Compiler();

    void run();

private:
    void _runTokenizer();
};

#endif		// !COMPILER_HH_
