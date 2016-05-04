#include "BNFRule.hh"
#include <iostream>

SyntacticAnalyzer::BNFRule::BNFRule(std::map<std::string, BNFRule *> &grammarMap,
                                    const std::vector<std::string> &input)
    : _grammarMap(grammarMap), _stringDefinition(input), _initStarted(false),
    _isRoot(false), _repetitionMin(1), _repetitionMax(1), _name(NULL), _expectedValue(NULL),
    _expectedToken(Tokenizer::Token::eType::UNKNOWN)
{
}

SyntacticAnalyzer::BNFRule::~BNFRule()
{
}

bool SyntacticAnalyzer::BNFRule::init()
{
    return (_initName() && _initRoot());
}

void SyntacticAnalyzer::BNFRule::printCurrentRule()
{
    std::cout << "Current rule: ";
    for (std::string elem : _stringDefinition)
    {
        std::cout << elem << ", ";
    }
    std::cout << std::endl;
}

bool SyntacticAnalyzer::BNFRule::_ruleAlreadyInitializing()
{
    if (_initStarted)
    {
        std::cout << "|X| RULE ALREADY INITIALIZING" << std::endl;
        return true;
    }
    _initStarted = true;
    std::cout << std::endl << "|O| START RULE INITIALIZATION" << std::endl;
    return false;
}

bool SyntacticAnalyzer::BNFRule::createTree()
{
    if (_ruleAlreadyInitializing())
        return true;
    if (_stringDefinition.size() > 2)
    {
        printCurrentRule();
        for (unsigned int i = 2; i != _stringDefinition.size(); ++i)
        {
            if (!_interpretRuleElement(i))
                return false;
        }
        std::cout << "EOL" << std::endl;
        return (true);
    }
    std::cerr << "Error: Not enough data to construct rule" << std::endl;
    return (false);
}

bool SyntacticAnalyzer::BNFRule::_interpretRuleElement(unsigned int &i)
{
    if (_stringDefinition[i].size() == 1)
    {
        if (!_interpretSoloCharRuleElement(i))
            return false;
    }
    else
    {
        if (!_interpretStringRuleElement(i))
            return false;
    }
    return true;
}

bool SyntacticAnalyzer::BNFRule::_interpretSoloCharRuleElement(unsigned int &i)
{
    switch (_stringDefinition[i][0])
    {
    case (eBNFToken::CONCATENATION):
        std::cout << "CONCATENATION, ";
        break;
    case (eBNFToken::ALTERNATIVE):
        std::cout << "ALTERNATIVE, ";
        break;
    case (eBNFToken::SEQUENCE_OPEN):
        std::cout << "SEQUENCE_OPEN, ";
        break;
    case (eBNFToken::SEQUENCE_CLOSE):
        std::cout << "SEQUENCE_CLOSE, ";
        break;
    case (eBNFToken::BURN_UNTIL_EOL):
        std::cout << "BURN_UNTIL_EOL, ";
        i = _stringDefinition.size() - 1;
        break;
    case (eBNFToken::EXISTING_TOKEN):
        std::cout << "EXISTING_TOKEN, ";
        if (i + 1 <= _stringDefinition.size())
        {
            ++i;
            _assignExistingToken(_stringDefinition[i]);
        }
        else
        {
            std::cout << "NO EXISTING_TOKEN, ";
        }
        break;
    default:
        std::cout << "SOLO CHAR NOT FOUND, ";
        break;
    }
    return true;
}

void SyntacticAnalyzer::BNFRule::_assignExistingToken(const std::string &tokenStr)
{
    if (tokenStr == "DIGITS")
        _expectedToken = Tokenizer::Token::eType::DIGITS;
    else if (tokenStr == "ALPHABET")
        _expectedToken = Tokenizer::Token::eType::ALPHABET;
    else if (tokenStr == "WORD_SEPARATORS")
        _expectedToken = Tokenizer::Token::eType::WORD_SEPARATORS;
    else if (tokenStr == "BLANK_SPACE")
        _expectedToken = Tokenizer::Token::eType::BLANK_SPACE;
    else if (tokenStr == "DOUBLE_QUOTES")
        _expectedToken = Tokenizer::Token::eType::DOUBLE_QUOTES;
    else if (tokenStr == "META")
        _expectedToken = Tokenizer::Token::eType::META;
    else if (tokenStr == "LABEL")
        _expectedToken = Tokenizer::Token::eType::LABEL;
    else if (tokenStr == "DIRECT")
        _expectedToken = Tokenizer::Token::eType::DIRECT;
    else if (tokenStr == "PARAMETER_SEPARATOR")
        _expectedToken = Tokenizer::Token::eType::PARAMETER_SEPARATOR;
    else if (tokenStr == "COMMENT")
        _expectedToken = Tokenizer::Token::eType::COMMENT;
    else
        _expectedToken = Tokenizer::Token::eType::UNKNOWN;
    std::cout << tokenStr << " -> numeric value = " << _expectedToken << ", ";
}

bool SyntacticAnalyzer::BNFRule::_interpretStringRuleElement(unsigned int &i)
{
    if (_stringDefinition[i].find('*') != std::string::npos)
    {
        std::cout << "REPETITION, ";
    }
    else if (_stringDefinition[i].size() > 2 &&
            _stringDefinition[i].find('\'') == 0 &&
            _stringDefinition[i].rfind('\'') == _stringDefinition[i].size() - 1)
    {
        std::string quotedString = _stringDefinition[i];

        std::cout << "QUOTE = ";
        quotedString.pop_back();
        quotedString = quotedString.substr(1);
        std::cout << quotedString << ", ";
        _expectedValue = new std::string(quotedString);
    }
    else
    {
        if (_grammarMap.find(_stringDefinition[i]) != _grammarMap.end())
        {
            std::cout << "FOUND SUB RULE " << _stringDefinition[i] << std::endl;
            if (!_grammarMap[_stringDefinition[i]]->createTree())
            {
                std::cout << std::endl << "AIE AIE AIE c'est pas bon" << std::endl;
                return false;
            }
            _tree.push_back(_grammarMap[_stringDefinition[i]]);
            std::cout << "OUT OF SUB RULE " << _stringDefinition[i] << std::endl << std::endl;
            printCurrentRule();
        }
    }
    return true;
}

bool SyntacticAnalyzer::BNFRule::_initName()
{
    if (_stringDefinition.size() > 0)
    {
        _name = (std::string *)(&(_stringDefinition[0]));
        std::cout << "New rule \"" << *_name << "\", ";
        return (true);
    }
    std::cerr << "Error: Invalid rule name" << std::endl;
    return (false);
}

bool SyntacticAnalyzer::BNFRule::_initRoot()
{
    if (_stringDefinition.size() > 1)
    {
        if (_stringDefinition[1] == "#")
            _isRoot = true;
        else if (_stringDefinition[1] != "=")
        {
            std::cerr << "Error: Invalid rule creation" << std::endl;
            return (false);
        }
        std::cout << (_isRoot ? "is ROOT, " : "") << std::endl;
        return (true);
    }
    return (false);
}

// bool SyntacticAnalyzer::BNFRule::valid() const
// {
//     return (true);
// }
//
// bool SyntacticAnalyzer::BNFRule::status() const
// {
//     return (true);
// }

const std::string *SyntacticAnalyzer::BNFRule::name() const
{
    return _name;
}

bool SyntacticAnalyzer::BNFRule::isRoot() const
{
    return _isRoot;
}

std::vector<SyntacticAnalyzer::BNFRule *> &SyntacticAnalyzer::BNFRule::subTree()
{
    return _tree;
}

const std::string *SyntacticAnalyzer::BNFRule::expectedValue() const
{
    return _expectedValue;
}

Tokenizer::Token::eType SyntacticAnalyzer::BNFRule::expectedToken() const
{
    return _expectedToken;
}

// void SyntacticAnalyzer::BNFRule::_createSubRuleFrom(const std::vector<std::string> &sequence)
// {
//     (void)sequence;
// }
