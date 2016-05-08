#include "GrammarRule.hh"
#include <iostream>

SyntacticAnalyzer::GrammarRule::~GrammarRule()
{
}

bool SyntacticAnalyzer::GrammarRule::parseLine(const std::vector<Tokenizer::Token> &inputLine)
{
    // std::cout << "\t\t\t\t ### 4242424242424242424242424242" << std::endl << std::endl;
    for (unsigned int i = 0; i != inputLine.size(); ++i)
    {
        std::cout << "[" << inputLine[i].raw << "] ";
    }
    std::cout << std::endl;

    unsigned int i = 0;
    if (_parse(inputLine, i))
    {
        // std::cout << "\t\t\t\t ### Input is valid" << std::endl << std::endl;
        std::cout << "### Input is valid" << std::endl << std::endl;
        return true;
    }
    // std::cout << "\t\t\t\t ### Input is invalid" << std::endl << std::endl;
    std::cout << "### Input is invalid" << std::endl << std::endl;
    return false;
}

bool SyntacticAnalyzer::GrammarRule::_parse(const std::vector<Tokenizer::Token> &inputLine, unsigned int &i)
{
    // std::cout << std::endl << "Current rule = " << *_name << " | i = " << i << " | Operator =  " << (char)_operator << " | " << _repetitionMin << "*" << _repetitionMax << std::endl;

    if (_subRule)
        return _parseSubRule(inputLine, i);

    if (_expectedToken != Tokenizer::Token::eType::UNKNOWN)
    {
        if (_parseToken(inputLine, i))
            return true;
    }
    else if (_expectedValue)
    {
        if (_parseStringValue(inputLine, i))
            return true;
    }
    else if (_burnUntilEOL == true)
        return _burnUntilEndOfLine(inputLine, i);

    if (_repetitionMin == 0)
        return true;

    // std::cout << "_parse() NOTHING valid found" << std::endl;
    // std::cout << "i = " << i << " | savedIndex = " << savedIndex << std::endl;
    return false;
}

bool SyntacticAnalyzer::GrammarRule::_parseSubRule(const std::vector<Tokenizer::Token> &inputLine, unsigned int &i)
{
    unsigned int savedIndex = i;

    // std::cout << "_parse() _subRule " << *_subRule->_name << " found" << std::endl;
    if (static_cast<GrammarRule *>(_subRule)->_parse(inputLine, i))
        return _parseValidSubRule(inputLine, i, savedIndex);
    return _parseInvalidSubRule(inputLine, i);
}

bool SyntacticAnalyzer::GrammarRule::_parseValidSubRule(const std::vector<Tokenizer::Token> &inputLine, unsigned int &i, unsigned int savedIndex)
{
    // std::cout << "sub rule " << *_subRule->_name << " is valid" << std::endl;

    while (static_cast<GrammarRule *>(_subRule)->_repetitionMax == (unsigned int)-1 &&
        static_cast<GrammarRule *>(_subRule)->_parse(inputLine, i));

    if (_next && static_cast<GrammarRule *>(_next)->_operator == OP_CONCATENATION)
    {
        // std::cout << "_parse() _next found" << std::endl;
        if (!static_cast<GrammarRule *>(_next)->_parse(inputLine, i))
        {
            // std::cout << "_parse() _next " << *_next->_name << " is invalid" << std::endl;
            i = savedIndex;
            return false;
        }
    }
    return true;
}

bool SyntacticAnalyzer::GrammarRule::_parseInvalidSubRule(const std::vector<Tokenizer::Token> &inputLine, unsigned int &i)
{
    GrammarRule *rule = static_cast<GrammarRule *>(static_cast<GrammarRule *>(_subRule)->_next);

    // std::cout << "BEFORE checking alternative" << std::endl;
    while (rule && rule->_operator == OP_ALTERNATIVE)
    {
        // std::cout << "Trying next alternative " << *rule->_name << std::endl;
        if (rule->_parse(inputLine, i))
            return true;
        rule = static_cast<GrammarRule *>(rule->_next);
    }

    // std::cout << "sub rule " << *_subRule->_name << " is invalid" << std::endl << std::endl;
    if (_repetitionMin == 0)
    {
        // std::cout << "But repetition min = 0, so it's okay" << std::endl;
        return true;
    }
    return false;
}

bool SyntacticAnalyzer::GrammarRule::_parseToken(const std::vector<Tokenizer::Token> &inputLine, unsigned int &i)
{
    // std::cout << "_parse() token != UNKNOWN | " << inputLine[i].type << " | " << _expectedToken << std::endl;
    if (inputLine[i].type == _expectedToken)
    {
        // std::cout << "input is valid" << std::endl;
        std::cout << "Found valid token | Type = " << _expectedToken << "\t| Value = ' " << inputLine[i].raw << " '" << std::endl;
        ++i;
        return true;
    }
    return false;
}

bool SyntacticAnalyzer::GrammarRule::_parseStringValue(const std::vector<Tokenizer::Token> &inputLine, unsigned int &i)
{
    // std::cout << "_parse() _expectedValue found" << std::endl;
    if (inputLine[i].raw == *_expectedValue)
    {
        // std::cout << "input is valid" << std::endl;
        std::cout << "Found valid string\t\t| Value = ' " << inputLine[i].raw << " '" << std::endl;
        ++i;
        return true;
    }
    return false;
}

bool SyntacticAnalyzer::GrammarRule::_burnUntilEndOfLine(const std::vector<Tokenizer::Token> &inputLine, unsigned int &i)
{
    // std::cout << "_parse() _burnUntilEOL found" << std::endl;
    std::cout << "Found burn until EOL" << std::endl;
    i = inputLine.size();
    return true;
}
