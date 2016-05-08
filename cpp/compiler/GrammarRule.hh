#ifndef		GRAMMAR_RULE_HH_
# define	GRAMMAR_RULE_HH_

# include "SyntacticAnalyzer.hh"
# include "BNFRule.hh"

class SyntacticAnalyzer::GrammarRule : public BNFRule
{
public:
    virtual ~GrammarRule();

    bool parseLine(const std::vector<Tokenizer::Token> &);

private:
    bool _parse(const std::vector<Tokenizer::Token> &, unsigned int &);
    bool _parseSubRule(const std::vector<Tokenizer::Token> &, unsigned int &);
    bool _parseValidSubRule(const std::vector<Tokenizer::Token> &, unsigned int &, unsigned int);
    bool _parseInvalidSubRule(const std::vector<Tokenizer::Token> &, unsigned int &);
    bool _parseToken(const std::vector<Tokenizer::Token> &, unsigned int &);
    bool _parseStringValue(const std::vector<Tokenizer::Token> &, unsigned int &);
    bool _burnUntilEndOfLine(const std::vector<Tokenizer::Token> &, unsigned int &);
};

#endif		// !GRAMMAR_RULE_HH_
