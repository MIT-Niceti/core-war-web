#include "BNFRule.hh"

const char SyntacticAnalyzer::BNFRule::creation = '=';
const char SyntacticAnalyzer::BNFRule::creationRoot = '#';
const char SyntacticAnalyzer::BNFRule::concatenation = '+';
const char SyntacticAnalyzer::BNFRule::alternative = '|';
const char SyntacticAnalyzer::BNFRule::sequenceOpen = '(';
const char SyntacticAnalyzer::BNFRule::sequenceClose = ')';
const char SyntacticAnalyzer::BNFRule::repetition = '*';
const char SyntacticAnalyzer::BNFRule::quote = '\'';
const char SyntacticAnalyzer::BNFRule::burnUntilEOF = '~';

SyntacticAnalyzer::BNFRule::BNFRule(const std::vector<std::string> &input)
    : _stringDefinition(input), _repetitionMin(1), _repetitionMax(1), _name(NULL), _value(NULL), _isRoot(false)
{
}

SyntacticAnalyzer::BNFRule::~BNFRule()
{
}

bool SyntacticAnalyzer::BNFRule::valid() const
{
    return (true);
}

bool SyntacticAnalyzer::BNFRule::status() const
{
    return (true);
}

void SyntacticAnalyzer::BNFRule::_createSubRuleFrom(const std::vector<std::string> &sequence)
{
    (void)sequence;
}
