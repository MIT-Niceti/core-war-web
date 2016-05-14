#ifndef		COMPILER_HH_
# define	COMPILER_HH_

# include "Tokenizer.hh"
# include <vector>
# include <string>

class		Compiler
{
private:
    const std::string _inputFile;
    const std::string _outputFile;
    TokensLines _tokenizedFile;

public:
    Compiler(const std::string &, const std::string &);
    ~Compiler();

    bool run();

private:
    void _runTokenizer();
};

#endif		// !COMPILER_HH_
