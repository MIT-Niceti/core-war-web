#include "Compiler.hh"
#include "SyntacticAnalyzer.hh"
#include <string>
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
    Tokenizer tokenizer;
    std::vector<Tokenizer::Token> *tokenizedLine = NULL;
    std::string line;

    _openInputFile();
    while (std::getline(_inputFileStream, line) && (tokenizedLine = tokenizer.tokenizeLine(line)))
    {
        if (!tokenizedLine->empty())
            _tokenizedFile.push_back(tokenizedLine);
    }
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
