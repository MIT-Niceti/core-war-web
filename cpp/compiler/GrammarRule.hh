#ifndef		GRAMMAR_RULE_HH_
# define	GRAMMAR_RULE_HH_

# include "SyntacticAnalyzer.hh"
# include "BNFRule.hh"

class SyntacticAnalyzer::GrammarRule : public BNFRule
{
public:
    virtual ~GrammarRule();

    bool parseLine(const TokensLine &);

private:
    bool _parse(const TokensLine &, unsigned int &);
    bool _parseSubRule(const TokensLine &, unsigned int &);
    bool _parseValidSubRule(const TokensLine &, unsigned int &, unsigned int);
    bool _parseInvalidSubRule(const TokensLine &, unsigned int &);
    bool _parseToken(const TokensLine &, unsigned int &);
    bool _parseStringValue(const TokensLine &, unsigned int &);
    bool _burnUntilEndOfLine(const TokensLine &, unsigned int &);
};

#endif		// !GRAMMAR_RULE_HH_
