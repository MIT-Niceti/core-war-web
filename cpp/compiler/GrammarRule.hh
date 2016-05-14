#ifndef		GRAMMAR_RULE_HH_
# define	GRAMMAR_RULE_HH_

# include "SyntacticAnalyzer.hh"
# include "BNFRule.hh"
# include "ParserOutput.hh"
# include "AOutput.hh"

class SyntacticAnalyzer::GrammarRule : public BNFRule
{
public:
    virtual ~GrammarRule();

    AOutput *parseLine(const TokensLine &);

private:
    bool _parse(const TokensLine &, unsigned int &, ParserOutput *);
    bool _parseSubRule(const TokensLine &, unsigned int &, ParserOutput *);
    bool _parseValidSubRule(const TokensLine &, unsigned int &, unsigned int, ParserOutput *);
    bool _parseInvalidSubRule(const TokensLine &, unsigned int &, ParserOutput *);
    bool _parseToken(const TokensLine &, unsigned int &, ParserOutput *);
    bool _parseStringValue(const TokensLine &, unsigned int &, ParserOutput *);
    bool _burnUntilEndOfLine(const TokensLine &, unsigned int &);
};

#endif		// !GRAMMAR_RULE_HH_
