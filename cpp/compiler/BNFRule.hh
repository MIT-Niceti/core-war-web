#ifndef		BNF_RULE_HH_
# define	BNF_RULE_HH_

# include "SyntacticAnalyzer.hh"
# include "Token.hh"
# include <map>
# include <vector>
# include <string>

class SyntacticAnalyzer::BNFRule
{
private:
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

    std::map<std::string, BNFRule *> &_grammarMap;

    const std::vector<std::string> _stringDefinition;
    std::vector<BNFRule *> _tree;
    bool _initStarted;

    // concerne UNIQUEMENT cette regle, et devrait la definir dans sa globalite
    bool _isRoot;
    unsigned int _repetitionMin;
    unsigned int _repetitionMax;
    std::string *_name;
    std::string *_expectedValue;
    Tokenizer::Token::eType _expectedToken;

public:
    BNFRule(std::map<std::string, BNFRule *> &, const std::vector<std::string> &);
    ~BNFRule();

    bool init();
    bool createTree();

private:
    void printCurrentRule(); // temp

    bool _ruleAlreadyInitializing();
    bool _interpretRuleElement(unsigned int &);
    bool _interpretSoloCharRuleElement(unsigned int &);
    void _assignExistingToken(const std::string &);
    bool _interpretStringRuleElement(unsigned int &);

    bool _initName();
    bool _initRoot();

public:
    // bool valid() const;
    // bool status() const;

    const std::string *name() const;
    bool isRoot() const;

    std::vector<BNFRule *> &subTree();

    const std::string *expectedValue() const;
    Tokenizer::Token::eType expectedToken() const;

// private:
//     void _createSubRuleFrom(const std::vector<std::string> &);
};

#endif		// !BNF_RULE_HH_
