#ifndef		BNF_RULE_HH_
# define	BNF_RULE_HH_

# include "SyntacticAnalyzer.hh"
# include <vector>
# include <string>

class SyntacticAnalyzer::BNFRule
{
private:
        static const char creation;
        static const char creationRoot;
        static const char concatenation;
        static const char alternative;
        static const char sequenceOpen;
        static const char sequenceClose;
        static const char repetition;
        static const char quote;
        static const char burnUntilEOF;

        const std::vector<std::string> _stringDefinition;
        std::vector<BNFRule *> _tree;
        std::vector<std::string> _repetitionString;
        unsigned int _repetitionMin;
        unsigned int _repetitionMax;
        std::string *_name;
        std::string *_value;
        bool _isRoot;

public:
        BNFRule(const std::vector<std::string> &);
        ~BNFRule();

        bool valid() const;
        bool status() const;

private:
        void _createSubRuleFrom(const std::vector<std::string> &);
};

#endif		// !BNF_RULE_HH_
