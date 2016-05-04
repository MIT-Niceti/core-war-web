#ifndef		COMPILER_HH_
# define	COMPILER_HH_

# include "Tokenizer.hh"
# include <fstream>
# include <vector>
# include <string>

class		Compiler
{
private:
    const std::string _inputFile;
    std::fstream _inputFileStream;
    std::vector<std::vector<Tokenizer::Token> *> _tokenizedFile;

public:
    Compiler(const std::string &);
    ~Compiler();

    void run();

private:
    void _openInputFile();
    void _closeInputFile();
    void _runTokenizer();
};

#endif		// !COMPILER_HH_
