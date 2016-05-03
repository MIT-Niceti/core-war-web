#include "Compiler.hh"
#include "Tokenizer.hh"
#include <string>
#include <iostream>
#include <vector>

Compiler::Compiler(const std::string &inputFile)
    : _inputFile(inputFile)
{
}

Compiler::~Compiler()
{
}

void Compiler::run()
{
    Tokenizer tokenizer;
    std::vector<std::vector<Tokenizer::Token> *> tokenizedFile;
    std::vector<Tokenizer::Token> *tokenizedLine = NULL;
    std::string line;

    _openInputFile();
    while (std::getline(_inputFileStream, line) && (tokenizedLine = tokenizer.tokenizeLine(line)))
    {
        // std::cout << "WAZA" << std::endl;
        tokenizedFile.push_back(tokenizedLine);

        unsigned int i = 0;
        while (i != tokenizedLine->size())
        {
            std::cout << "Token type: " << (*tokenizedLine)[i].type << " | "
                << "Raw token string: \"" << (*tokenizedLine)[i].raw << "\"" << std::endl;
            ++i;
        }
    }
    // std::cout << "AU REVOIR" << std::endl;
    _closeInputFile();
}

void Compiler::_openInputFile()
{
    std::cout << "Opening \"" << _inputFile << "\"..." << std::endl << std::endl;
    _inputFileStream.open(_inputFile.c_str(), std::fstream::in);
}

void Compiler::_closeInputFile()
{
    _inputFileStream.close();
}
