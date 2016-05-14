#ifndef		SYNTACTIC_ANALYZER_HH_
# define	SYNTACTIC_ANALYZER_HH_

# include "Tokenizer.hh"
# include "Token.hh"
# include "AOutput.hh"
# include <vector>
# include <map>
# include <string>

typedef std::vector<std::vector<std::string> > GrammarDeclaration;
typedef std::vector<std::string> GrammarRuleDeclaration;
typedef std::vector<AOutput *> ParsedLines;

class SyntacticAnalyzer
{
private:
    class BNFRule;
    class GrammarRule;

    static const GrammarDeclaration _grammar;
    std::map<std::string, BNFRule *> _grammarTree;
    BNFRule *_rootRule;

public:
    SyntacticAnalyzer();
    ~SyntacticAnalyzer();

    ParsedLines *createTree(const TokensLines &tokenizedFile);

private:
    bool _initGrammarMap();
    bool _initGrammarTree();
    ParsedLines *_parseInput(const TokensLines &tokenizedFile);
    // void _readCreatedGrammarTree(BNFRule *, int = 0);
};

#endif		// !SYNTACTIC_ANALYZER_HH_
