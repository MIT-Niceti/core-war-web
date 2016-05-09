#include "Compiler.hh"
#include "SyntacticAnalyzer.hh"
#include <string>
#include <fstream>
#include <iostream>

Compiler::Compiler(const std::string &inputFile)
    : _inputFile(inputFile)
{
}

Compiler::~Compiler()
{
}

void Compiler::run()
{
    SyntacticAnalyzer analyzer;
    void *tree = NULL;

    _runTokenizer();
    tree = analyzer.createTree(_tokenizedFile);
    (void)tree;
}

void Compiler::_runTokenizer()
{
    const TokensLine *tokenizedLine = NULL;
    std::fstream inputFileStream;
    Tokenizer tokenizer;
    std::string line;

    std::cout << "Opening \"" << _inputFile << "\"..." << std::endl << std::endl;
    inputFileStream.open(_inputFile.c_str(), std::fstream::in);
    if (inputFileStream.is_open())
    {
        while (std::getline(inputFileStream, line) && (tokenizedLine = tokenizer.tokenizeLine(line)))
        {
            if (!tokenizedLine->empty())
                _tokenizedFile.push_back(tokenizedLine);
            else
                delete tokenizedLine;
            tokenizedLine = NULL;
        }
    }
    else
        std::cerr << "Error while opening file" << std::endl;
    inputFileStream.close();
    std::cout << std::endl;
}
