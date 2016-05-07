#include "BNFRule.hh"
#include <sstream>
#include <iostream>

SyntacticAnalyzer::BNFRule::BNFRule(std::map<std::string, BNFRule *> &grammarMap,
                                    const std::vector<std::string> &input)
    : _grammarMap(grammarMap), _stringDefinition(input), _next(NULL), _prev(NULL),
    _name(NULL), _isRoot(false), _initStarted(false),
    _repetitionMin(1), _repetitionMax(1), _operator(eBNFOperator::OP_CONCATENATION),
    _subRule(NULL), _expectedValue(NULL), _expectedToken(Tokenizer::Token::eType::UNKNOWN), _burnUntilEOL(false)
{
}

SyntacticAnalyzer::BNFRule::~BNFRule()
{
}

bool SyntacticAnalyzer::BNFRule::init()
{
    return (_initName() && _initRoot());
}

bool SyntacticAnalyzer::BNFRule::_ruleAlreadyInitializing()
{
    if (_initStarted)
        return true;
    _initStarted = true;
    return false;
}

bool SyntacticAnalyzer::BNFRule::createTree()
{
    if (_ruleAlreadyInitializing())
        return true;
    if (_stringDefinition.size() > 2)
    {
        _name = (std::string *)&(_stringDefinition[0]);
        for (unsigned int i = 2; i < _stringDefinition.size(); ++i)
        {
            if (!_interpretRuleElement(i))
                return false;
        }
        return (true);
    }
    std::cerr << "Error: Not enough data to construct rule" << std::endl;
    return (false);
}

bool SyntacticAnalyzer::BNFRule::_constructElem(unsigned int &i)
{
    _name = (std::string *)&(_stringDefinition[i]);
    while (i < _stringDefinition.size())
    {
        if (!_interpretRuleElement(i))
            return false;
        ++i;
    }
    return true;
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
    BNFRule *nextElem = NULL;
    std::vector<std::string> generatedSubRule;
    std::string generatedSubRuleName;

    switch (_stringDefinition[i][0])
    {
    case (eBNFToken::CONCATENATION):
        nextElem = new BNFRule(_grammarMap, _stringDefinition);
        nextElem->_operator = eBNFOperator::OP_CONCATENATION;
        _pushBack(nextElem);
        nextElem->_constructElem(++i);
        break;
    case (eBNFToken::ALTERNATIVE):
        nextElem = new BNFRule(_grammarMap, _stringDefinition);
        nextElem->_operator = eBNFOperator::OP_ALTERNATIVE;
        _pushBack(nextElem);
        nextElem->_constructElem(++i);
        break;
    case (eBNFToken::SEQUENCE_OPEN):
        generatedSubRuleName = "SubRuleOf" + *(_getCurrentRuleRoot()->_name) + "Generated";
        generatedSubRule.push_back(generatedSubRuleName);
        generatedSubRule.push_back("=");

        ++i;
        while (i != _stringDefinition.size() && _stringDefinition[i][0] != eBNFToken::SEQUENCE_CLOSE)
        {
            generatedSubRule.push_back(_stringDefinition[i]);
            ++i;
        }

        nextElem = new BNFRule(_grammarMap, generatedSubRule);
        _grammarMap[generatedSubRuleName] = nextElem;
        nextElem->createTree();
        _subRule = nextElem;

        break;
    case (eBNFToken::SEQUENCE_CLOSE):
        break;
    case (eBNFToken::BURN_UNTIL_EOL):
        i = _stringDefinition.size() - 1;
        _burnUntilEOL = true;
        break;
    case (eBNFToken::EXISTING_TOKEN):
        if (i + 1 <= _stringDefinition.size())
        {
            ++i;
            _assignExistingToken(_stringDefinition[i]);
        }
        break;
    default:
        return false;
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
}

bool SyntacticAnalyzer::BNFRule::_interpretStringRuleElement(unsigned int &i)
{
    if (_stringDefinition[i].find('*') != std::string::npos)
    {
        std::string min, max;

        min = _stringDefinition[i].substr(0, _stringDefinition[i].find('*'));
        max = _stringDefinition[i].substr(_stringDefinition[i].find('*') + 1);

        std::stringstream convert(min);
        if (!(convert >> _repetitionMin))
            _repetitionMin = 1;

        if (max != "x")
        {
            convert = std::stringstream(max);
            if (!(convert >> _repetitionMax))
                _repetitionMax = 1;
        }
        else
        {
            _repetitionMax = (unsigned int)-1;
        }
    }
    else if (_stringDefinition[i].size() > 2 &&
            _stringDefinition[i].find('\'') == 0 &&
            _stringDefinition[i].rfind('\'') == _stringDefinition[i].size() - 1)
    {
        std::string quotedString = _stringDefinition[i];

        quotedString.pop_back();
        quotedString = quotedString.substr(1);
        _expectedValue = new std::string(quotedString);
    }
    else
    {
        if (_grammarMap.find(_stringDefinition[i]) != _grammarMap.end())
        {
            if (!_grammarMap[_stringDefinition[i]]->createTree())
                return false;
            _subRule = _grammarMap[_stringDefinition[i]];
        }
        else
        {
            std::cerr << "Unknown BNF rule \"" << _stringDefinition[i] << "\"" << std::endl;
            return false;
        }
    }
    return true;
}

bool SyntacticAnalyzer::BNFRule::_initName()
{
    if (_stringDefinition.size() > 0)
    {
        _name = (std::string *)(&(_stringDefinition[0]));
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
        return (true);
    }
    return (false);
}

void SyntacticAnalyzer::BNFRule::_pushBack(SyntacticAnalyzer::BNFRule *elem)
{
    BNFRule *last = this;

    while (last && last->_next)
        last = last->_next;
    last->_next = elem;
    elem->_prev = last;
}

const std::string *SyntacticAnalyzer::BNFRule::name() const
{
    return _name;
}

bool SyntacticAnalyzer::BNFRule::isRoot() const
{
    return _isRoot;
}

const std::string *SyntacticAnalyzer::BNFRule::expectedValue() const
{
    return _expectedValue;
}

Tokenizer::Token::eType SyntacticAnalyzer::BNFRule::expectedToken() const
{
    return _expectedToken;
}

SyntacticAnalyzer::BNFRule *SyntacticAnalyzer::BNFRule::_getCurrentRuleRoot()
{
    BNFRule *root = this;

    while (root->_prev)
        root = root->_prev;
    return root;
}
