#include "SyntacticAnalyzer.hh"
#include "BNFRule.hh"
#include "GrammarRule.hh"
#include <iostream>

const GrammarDeclaration SyntacticAnalyzer::_grammar =
{
    { "decimalNumber", "=", "^", "DIGITS" },
    { "alphaWord", "=", "^", "ALPHABET" },
    { "wordSeparator", "=", "^", "WORD_SEPARATORS" },
    { "blankSpace", "=", "^", "BLANK_SPACE" },
    { "doubleQuotes", "=", "^", "DOUBLE_QUOTES" },
    { "metaChar", "=", "^", "META" },
    { "labelChar", "=", "^", "LABEL" },
    { "directChar", "=", "^", "DIRECT" },
    { "parameterSeparatorChar", "=", "^", "PARAMETER_SEPARATOR" },
    { "commentChar", "=", "^", "COMMENT" },

    { "anyChar", "=", "~" },

    { "optionalBlankSpace", "=", "blankSpace", "0*1" },

    { "alphaNumericWord", "=", "(", "decimalNumber", "|", "alphaWord", "|", "wordSeparator", ")", "1*x" },

    { "acceptableQuotedStr", "=", "(", "decimalNumber", "|", "alphaWord", "|", "blankSpace", "|", "wordSeparator", ")", "1*x" },
    { "quotedStr", "=", "doubleQuotes", "+", "acceptableQuotedStr", "+", "doubleQuotes" },

    { "nameStr", "=", "'name'" },
    { "commentStr", "=", "'comment'" },
    { "metaName", "=", "metaChar", "+", "nameStr" },
    { "metaComment", "=", "metaChar", "+", "commentStr" },

    { "language", "#", "validLine" },
    { "validLine", "=", "optionalBlankSpace", "+", "assemblyLine" },

    { "assemblyLine", "=", "declarativeLine", "|", "commentedLine" },
    { "declarativeLine", "=", "assemblyDeclaration", "+", "optionalBlankSpace", "+", "optionalDeveloperComment" },
    { "commentedLine", "=", "developerComment" },

    { "optionalDeveloperComment", "=", "developerComment", "0*1" },
    { "developerComment", "=", "commentChar", "+", "anyChar" },

    { "metaNameDeclaration", "=", "metaName", "+", "blankSpace", "+", "quotedStr" },
    { "metaCommentDeclaration", "=", "metaComment", "+", "blankSpace", "+", "quotedStr" },

    { "assemblyDeclaration", "=", "metaNameDeclaration", "|", "metaCommentDeclaration", "|", "labelAndInstructionDeclaration", "|", "instructionDeclaration", "|", "labelDeclaration" },

    { "instructionDeclaration", "=", "instructionName", "+", "optionalBlankSpace", "+", "instructionParameters" },
    { "labelAndInstructionDeclaration", "=", "labelDeclaration", "+", "optionalBlankSpace", "+", "instructionDeclaration" },

    { "firstParameter", "=", "instructionParameter" },
    { "nthParameter", "=", "(", "optionalBlankSpace", "+", "parameterSeparatorChar", "+", "optionalBlankSpace", "+", "instructionParameter", ")", "0*16" },
    { "instructionParameters", "=", "firstParameter", "+", "nthParameter" },

    { "instructionParameter", "=", "registerParameter", "|", "directValueParameter", "|", "indirectValueParameter" },

    { "registerParameter", "=", "'r'", "+", "decimalNumber" },
    { "directValue", "=", "decimalNumber", "|", "labelValue" },
    { "directValueParameter", "=", "directChar", "+", "optionalBlankSpace", "+", "directValue" },
    { "indirectValueParameter", "=", "decimalNumber", "|", "labelValue" },

    { "labelDeclaration", "=", "alphaNumericWord", "+", "optionalBlankSpace", "+", "labelChar" },
    { "labelValue", "=", "labelChar", "+", "optionalBlankSpace", "+", "alphaNumericWord" },

    { "instructionName", "=", \
        "'live'", "|", \
        "'ld'", "|", \
        "'st'", "|", \
        "'add'", "|", \
        "'sub'", "|", \
        "'and'", "|", \
        "'or'", "|", \
        "'xor'", "|", \
        "'zjmp'", "|", \
        "'ldi'", "|", \
        "'sti'", "|", \
        "'fork'", "|", \
        "'lld'", "|", \
        "'lldi'", "|", \
        "'lfork'", "|", \
        "'print'"
    }
};

SyntacticAnalyzer::SyntacticAnalyzer()
    : _rootRule(NULL)
{
}

SyntacticAnalyzer::~SyntacticAnalyzer()
{
}

ParsedLines *SyntacticAnalyzer::createTree(const TokensLines &tokenizedFile)
{
    if (!_initGrammarMap() || !_initGrammarTree())
        return NULL;

    // std::cout << std::endl;
    // _readCreatedGrammarTree(_rootRule);

    return _parseInput(tokenizedFile);
}

bool SyntacticAnalyzer::_initGrammarMap()
{
    for (GrammarRuleDeclaration grammarRule : _grammar)
    {
        BNFRule *rule = NULL;

        if (!(rule = new BNFRule(_grammarTree, grammarRule)))
        {
            std::cerr << "Error: Cannot allocate new BNFRule()" << std::endl;
            return false;
        }
        if (!rule->init())
        {
            std::cerr << "Error: SyntacticAnalyze, invalid grammar rule" << std::endl;
            return false;
        }
        if (_grammarTree.find(*(rule->name())) != _grammarTree.end())
        {
            std::cerr << "Error: SyntacticAnalyzer, duplicate rule" << std::endl;
            return false;
        }
        if (rule->isRoot() && _rootRule)
        {
            std::cerr << "Error: SyntacticAnalyzer, multiple main rule" << std::endl;
            return false;
        }
        else if (rule->isRoot())
            _rootRule = rule;
        _grammarTree[*(rule->name())] = rule;
    }
    return true;
}

bool SyntacticAnalyzer::_initGrammarTree()
{
    if (!_rootRule)
    {
        std::cerr << "Error: SyntacticAnalyzer, no root rule" << std::endl;
        return false;
    }
    return _rootRule->createTree();
}

ParsedLines *SyntacticAnalyzer::_parseInput(const TokensLines &tokenizedFile)
{
    GrammarRule *rootRule = static_cast<GrammarRule *>(_rootRule);
    ParsedLines *output = new ParsedLines;
    AOutput *tmp = NULL;

    for (unsigned int line = 0; line != tokenizedFile.size(); ++line)
    {
        if (!(tmp = rootRule->parseLine(*tokenizedFile[line])))
            return NULL;
        output->push_back(tmp);
        // rootRule->parseLine(*tokenizedFile[line]);
    }
    if (output->empty())
    {
        delete output;
        output = NULL;
    }
    return output;
}

// // Debug
// void SyntacticAnalyzer::_readCreatedGrammarTree(BNFRule *rule, int level)
// {
//     BNFRule *next = rule;
//     std::string tabulations;
//
//     for (int i = 0; i != level; ++i)
//     {
//         tabulations += "\t";
//     }
//
//     std::cout << tabulations;
//     std::cout << (rule->name() ? *(rule->name()) : "Unknown name") << " = ";
//
//     while (next)
//     {
//         std::cout << (char)next->_operator << " ";
//         if (next->_subRule)
//         {
//             std::cout << (next->_subRule->name() ? *(next->_subRule->name()) : "Unknown name");
//         }
//         else if (next->_expectedValue)
//         {
//             std::cout << "\"" << *(next->_expectedValue) << "\"";
//         }
//         else if (next->_expectedToken != Token::eType::UNKNOWN)
//         {
//             std::cout << next->_expectedToken;
//         }
//         else if (next->_burnUntilEOL)
//         {
//             std::cout << "burnUntilEOL";
//         }
//         else
//         {
//             std::cout << "Unknown expected value/rule";
//         }
//         std::cout << " (" << next->_repetitionMin << "*";
//         if (next->_repetitionMax == (unsigned int)-1)
//         {
//             std::cout << "x" << ")";
//         }
//         else
//         {
//             std::cout << next->_repetitionMax << ")";
//         }
//         std::cout << " ";
//         next = next->_next;
//     }
//     std::cout << std::endl;
//
//     next = rule;
//     while (next)
//     {
//         if (next->_subRule)
//         {
//             _readCreatedGrammarTree(next->_subRule, level + 1);
//         }
//         next = next->_next;
//     }
// }
