#ifndef		BNF_RULE_HH_
# define	BNF_RULE_HH_

# include "SyntacticAnalyzer.hh"
# include "Token.hh"
# include <map>
# include <vector>
# include <string>

class SyntacticAnalyzer::BNFRule
{
protected:
    enum eBNFToken : char
    {
        CREATION = '=',
        CREATION_ROOT = '#',
        CONCATENATION = '+',
        ALTERNATIVE = '|',
        SEQUENCE_OPEN = '(',
        SEQUENCE_CLOSE = ')',
        REPETITION = '*',
        QUOTE = '\'',
        BURN_UNTIL_EOL = '~',
        EXISTING_TOKEN = '^',
        UNKNOWN = '\0'
    };

    enum eBNFOperator : char
    {
        OP_CONCATENATION = '+',
        OP_ALTERNATIVE = '|',
        OP_UNKNOWN = '\0',
    };

    std::map<std::string, BNFRule *> &_grammarMap;

    const std::vector<std::string> _stringDefinition;
    BNFRule *_next;
    BNFRule *_prev;

    std::string *_name;
    bool _isRoot;
    bool _initStarted;

    // Rule validity conditions
    unsigned int _repetitionMin;
    unsigned int _repetitionMax;
    eBNFOperator _operator;

    // Define the rule validity
    BNFRule *_subRule;
    std::string *_expectedValue;
    Token::eType _expectedToken;
    bool _burnUntilEOL;

public:
    BNFRule(std::map<std::string, BNFRule *> &, const std::vector<std::string> &);
    ~BNFRule();

    bool init();
    bool createTree();

protected:
    bool _constructElem(unsigned int &);

    bool _ruleAlreadyInitializing();
    bool _interpretRuleElement(unsigned int &);
    bool _interpretSoloCharRuleElement(unsigned int &);
    void _assignExistingToken(const std::string &);
    bool _interpretStringRuleElement(unsigned int &);

    bool _initName();
    bool _initRoot();

    void _pushBack(BNFRule *);

public:
    const std::string *name() const;
    bool isRoot() const;

    const std::string *expectedValue() const;
    Token::eType expectedToken() const;

protected:
    BNFRule *_getCurrentRuleRoot();
};

#endif		// !BNF_RULE_HH_
