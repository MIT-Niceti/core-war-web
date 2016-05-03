#ifndef		COMPILER_HH_
# define	COMPILER_HH_

# include <fstream>
# include <string>

class		Compiler
{
private:
    const std::string _inputFile;
    std::fstream _inputFileStream;

public:
    Compiler(const std::string &);
    ~Compiler();

    void run();

private:
    void _openInputFile();
    void _closeInputFile();
};

#endif		// !COMPILER_HH_
