#include "GrammarRule.hh"
#include <iostream>

SyntacticAnalyzer::GrammarRule::~GrammarRule()
{
}

AOutput *SyntacticAnalyzer::GrammarRule::parseLine(const TokensLine &inputLine)
{
    ParserOutput *outputGenerator = new ParserOutput;
    AOutput *output = NULL;

    // std::cout << "\t\t\t\t ### 4242424242424242424242424242" << std::endl << std::endl;
    for (unsigned int i = 0; i != inputLine.size(); ++i)
    {
        std::cout << "[" << inputLine[i]->raw() << "] ";
    }
    std::cout << std::endl;

    unsigned int i = 0;
    if (_parse(inputLine, i, outputGenerator))
    {
        // std::cout << "\t\t\t\t ### Input is valid" << std::endl << std::endl;
        output = outputGenerator->finalizeOutput();
        std::cout << "### Input is valid" << std::endl << std::endl;
        return output;
    }
    // std::cout << "\t\t\t\t ### Input is invalid" << std::endl << std::endl;
    std::cout << "### Input is invalid" << std::endl << std::endl;
    return output;
}

bool SyntacticAnalyzer::GrammarRule::_parse(const TokensLine &inputLine, unsigned int &i, ParserOutput *output)
{
    unsigned int ruleIndexStart = i;

    // std::cout << std::endl << "Current rule = " << *_getCurrentRuleRoot()->_name << "->" << *_name
    //     << " | Operator =  '" << (char)_operator
    //     << "' | " << _repetitionMin << "*" << _repetitionMax << std::endl;
    // std::cout << "i = " << i << " | inputLine.size() = " << inputLine.size() << std::endl;
    if (_subRule)
    {
        // std::cout << "Found sub rule" << std::endl;
        if (static_cast<GrammarRule *>(_subRule)->_parseSubRule(inputLine, i, output))
        {
            output->constructOutput(*_subRule->name(), ruleIndexStart, i);
            return true;
        }
        return false;
    }

    if (_expectedToken != Token::eType::UNKNOWN)
    {
        if (_parseToken(inputLine, i, output))
            return true;
    }
    else if (_expectedValue)
    {
        if (_parseStringValue(inputLine, i, output))
            return true;
    }
    else if (_burnUntilEOL == true)
        return _burnUntilEndOfLine(inputLine, i);

    if (_repetitionMin == 0)
        return true;

    // std::cout << "_parse() NOTHING valid found" << std::endl;
    // std::cout << "i = " << i << std::endl;
    return false;
}

bool SyntacticAnalyzer::GrammarRule::_parseSubRule(const TokensLine &inputLine, unsigned int &i, ParserOutput *output)
{
    unsigned int savedIndex = i;

    // std::cout << "Checking sub rule " << *_getCurrentRuleRoot()->_name << "->" << *_name << "..." << std::endl;
    if (_parse(inputLine, i, output))
        return _parseValidSubRule(inputLine, i, savedIndex, output);
    return _parseInvalidSubRule(inputLine, i, output);
}

bool SyntacticAnalyzer::GrammarRule::_parseValidSubRule(const TokensLine &inputLine, unsigned int &i, unsigned int savedIndex, ParserOutput *output)
{
    unsigned int repetition = 0;

    // std::cout << "Sub rule " << *_getCurrentRuleRoot()->_name << "->" << *_name << " is valid" << std::endl;
    // std::cout << "But before should be repeat the sub rule " << *_getCurrentRuleRoot()->_name << "->" << *_name << " ?.." << std::endl;
    while (++repetition != _repetitionMax && _parse(inputLine, i, output));
    // {
    //     // std::cout << "Yes, current sub rule " << *_getCurrentRuleRoot()->_name << "->" << *_name << " repeated once" << std::endl;
    // }

    if (_next)
    {
        // std::cout << "Checking if there is some next elements for sub rule " << *_getCurrentRuleRoot()->_name << "->" << *_name  << "..." << std::endl;
        GrammarRule *next = static_cast<GrammarRule *>(_next);
        while (next && next->_operator == OP_CONCATENATION)
        {
            // std::cout << "Yes there is some next elements for " << *_getCurrentRuleRoot()->_name << "->" << *_name << ", checking rule validity..." << std::endl;
            // std::cout << "Next element is " << *next->_getCurrentRuleRoot()->_name << "->" << *next->_name << std::endl;
            if (!next->_parse(inputLine, i, output))
            {
                // std::cout << "Next sub rule element " << *next->_getCurrentRuleRoot()->_name << "->" << *next->_name << " is invalid" << std::endl << std::endl;
                i = savedIndex;
                return false;
            }
            // std::cout << "Next sub rule element " << *next->_getCurrentRuleRoot()->_name << "->" << *next->_name << " is valid" << std::endl << std::endl;
            next = static_cast<GrammarRule *>(next->_next);
        }
    }
    return true;
}

bool SyntacticAnalyzer::GrammarRule::_parseInvalidSubRule(const TokensLine &inputLine, unsigned int &i, ParserOutput *output)
{
    // std::cout << "Sub rule " << *_getCurrentRuleRoot()->_name << "->" << *_name << " is invalid, checking alternative or repetition escapes" << std::endl;
    if (_next)
    {
        GrammarRule *alt = static_cast<GrammarRule *>(_next);

        // std::cout << "Is there any alternative for " << *_getCurrentRuleRoot()->_name << "->" << *_name << " ?" << std::endl;
        while (alt && alt->_operator == OP_ALTERNATIVE)
        {
            // std::cout << "Yeah, one alternative found, checking validity..." << std::endl;
            if (alt->_parse(inputLine, i, output))
            {
                // std::cout << "Alternative found for " << *_getCurrentRuleRoot()->_name << "->" << *_name << std::endl << std::endl;
                alt = static_cast<GrammarRule *>(alt->_getCurrentRuleRoot());
                return true;
            }
            // std::cout << "Checking next alternative..." << std::endl;
            alt = static_cast<GrammarRule *>(alt->_next);
        }
    }
    if (_repetitionMin == 0)
    {
        // std::cout << "But repetition = 0 it's okay" << std::endl << std::endl;
        return true;
    }
    // std::cout << "Sub rule " << *_getCurrentRuleRoot()->_name << "->" << *_name << " is invalid" << std::endl << std::endl;
    return false;
}

bool SyntacticAnalyzer::GrammarRule::_parseToken(const TokensLine &inputLine, unsigned int &i, ParserOutput *output)
{
    // std::cout << "_parse() token != UNKNOWN | " << _expectedToken << std::endl;
    if (i < inputLine.size() && inputLine[i]->type() == _expectedToken)
    {
        // std::cout << "Found valid token | Type = " << _expectedToken << "\t| Value = ' " << inputLine[i]->raw() << " '" << std::endl;
        output->addElement(inputLine[i], i);
        ++i;
        return true;
    }
    else if (i >= inputLine.size() && _repetitionMin == 0)
    {
        // std::cout << "_parseToken | i >= inputLine.size() && _repetitionMin == 0 -> return true" << std::endl;
        return true;
    }
    return false;
}

bool SyntacticAnalyzer::GrammarRule::_parseStringValue(const TokensLine &inputLine, unsigned int &i, ParserOutput *output)
{
    // std::cout << "_parse() _expectedValue found" << std::endl;
    if (i < inputLine.size() && inputLine[i]->raw() == *_expectedValue)
    {
        // std::cout << "Found valid string\t\t| Value = ' " << inputLine[i]->raw() << " '" << std::endl;
        output->addElement(inputLine[i], i);
        ++i;
        return true;
    }
    else if (i >= inputLine.size() && _repetitionMin == 0)
    {
        // std::cout << "_parseStringValue | i >= inputLine.size() && _repetitionMin == 0 -> return true" << std::endl;
        return true;
    }
    return false;
}

bool SyntacticAnalyzer::GrammarRule::_burnUntilEndOfLine(const TokensLine &inputLine, unsigned int &i)
{
    // std::cout << "_parse() _burnUntilEOL found" << std::endl;
    i = inputLine.size();
    return true;
}
