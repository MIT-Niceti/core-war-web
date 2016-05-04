#include "SyntacticAnalyzer.hh"
#include <iostream>

const std::vector<std::vector<std::string>> SyntacticAnalyzer::_grammar =
{
    { "decimalNumber", "=", "^", "DIGITS" },
    { "alphaWord", "=", "^", "ALPHABET" },
    { "wordSeparator", "=", "^", "WORD_SEPARATOR" },
    { "blankSpace", "=", "^", "BLANK_SPACE" },
    { "doubleQuotes", "=", "^", "DOUBLE_QUOTES" },
    { "metaChar", "=", "^", "META" },
    { "labelChar", "=", "^", "LABEL" },
    { "directChar", "=", "^", "DIRECT" },
    { "parameterSeparatorChar", "^", "PARAMETER_SEPARATOR" },
    { "commentChar", "=", "^", "COMMENT" },

    { "anyChar", "=", "~" },

    { "alphaNumericWord", "=", "(", "decimalNumber", "|", "alphaWord", "|", "wordSeparator", ")", "1*x" },

    { "acceptableQuotedStr", "=", "(", "decimalNumber", "|", "alphaWord", "|", "blankSpace", "|", "wordSeparator", ")", "0*x" },
    { "quotedStr", "=", "(", "doubleQuotes", "+", "acceptableQuotedStr", "+", ")", "1*1" },

    { "nameStr", "=", "'name'", "1*1" },
    { "commentStr", "=", "'comment'", "1*1" },
    { "metaName", "=", "(", "metaChar", "+", "nameStr", ")", "1*1" },
    { "metaComment", "=", "(", "metaChar", "+", "commentStr", ")", "1*1" },

    { "language", "#", "validLine", "0*1" },
    { "validLine", "=", "(", "(", "blankSpace", "0*1", ")", "+", "(", "declarativeLine", "|", "commentedLine", ")", ")", "1*1" },

    { "declarativeLine", "=", "(", "assemblyDeclaration", "+", "(", "blankSpace", "0*1" ")", "+", "(", "developerComment", "0*1", ")", ")", "1*1" },
    { "commentedLine", "=", "developerComment", "1*1" },

    { "developerComment", "=", "(", "commentChar", "+", "anyChar", ")", "1*1" },

    {"metaNameDeclaration", "=", "(", "metaName", "blankSpace", "quotedStr", ")", "1*1" },
    {"metaCommentDeclaration", "=", "(", "metaComment", "blankSpace", "quotedStr", ")", "1*1" },

    { "assemblyDeclaration", "=", "(", "metaNameDeclaration", "+", "metaCommentDeclaration", "+", "labelDeclaration", "+", "instructionDeclaration", "+", "labelAndInstructionDeclaration", ")", "1*1" },

    { "instructionDeclaration", "=", "(", "instructionName", "(", "blankSpace", "0*1", ")", "instructionParameters", ")", "1*1" },
    { "labelAndInstructionDeclaration", "=", "(", "labelDeclaration", "(", "blankSpace", "0*1", ")", "instructionDeclaration", ")", "1*1" },

    { "firstParameter", "=", "instructionParameter", "1*1" },
    { "nthParameter", "=", "(", "parameterSeparatorChar", "+", "(", "blankSpace", "0*1", ")", "+", "instructionParameter", ")", "1*1" },
    { "instructionParameters", "=", "(", "(", "(", "firstParameter", "1*1", ")", "(", "blankSpace", "0*1", ")", "(", "nthParameter", "1*1", ")", "0*x", ")", ")", "1*1" },

    { "instructionParameter", "=", "(", "registerParameter", "+", "directValueParameter", "+", "indirectValueParameter", ")", "1*1" },

    { "registerParameter", "=", "(", "'r'", "+", "decimalNumber", ")", "1*1" },
    { "directValueParameter", "=", "(", "directChar", "+", "(", "blankSpace", "0*1", ")", "+", "(", "decimalNumber", "|", "labelValue", ")", ")", "1*1" },
    { "indirectValueParameter", "=", "(", "decimalNumber", "|", "labelValue", ")", "1*1" },

    { "labelDeclaration", "=", "(", "alphaNumericWord", "+", "(", "blankSpace", "0*1", ")", "+", "labelChar", ")", "1*1" },
    { "labelValue", "=", "(", "labelChar", "+", "(", "blankSpace", "0*1", ")", "+", "alphaNumericWord", ")", "1*1" },

    { "instructionName", "=", "(", \
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
        "'print'", \
     ")", "1*1" }
};

SyntacticAnalyzer::SyntacticAnalyzer()
{
}

SyntacticAnalyzer::~SyntacticAnalyzer()
{
}

void *SyntacticAnalyzer::createTree(const std::vector<std::vector<Tokenizer::Token> *> &tokenizedFile)
{
    unsigned int j = 0;
    while (j != tokenizedFile.size())
    {
        unsigned int i = 0;
        while (i != tokenizedFile[j]->size())
        {
            std::cout << "Token type: " << (*tokenizedFile[j])[i].type << " | "
                << "Raw token string: \"" << (*tokenizedFile[j])[i].raw << "\"" << std::endl;
            ++i;
        }
        if (i == 0)
            std::cout << "Empty line" << std::endl;
        std::cout << std::endl;
        ++j;
    }

    //
    if (!_initGrammarTree())
        return NULL;

    return NULL;
}

bool SyntacticAnalyzer::_initGrammarTree()
{
    for (std::vector<std::string> grammarRule : _grammar)
    {
        BNFRule *rule = NULL;

        if (grammarRule.size() < 3 || _grammarTree[grammarRule[0]] || !(rule = new BNFRule(grammarRule)))
        {
            std::cerr << "Error: SyntacticAnalyzer::_initGrammarTree()" << std::endl;
            return false;
        }
        _grammarTree[grammarRule[0]] = rule;
    }
    return true;
}
