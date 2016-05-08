#ifndef		SYNTACTIC_ANALYZER_HH_
# define	SYNTACTIC_ANALYZER_HH_

# include "Tokenizer.hh"
# include <vector>
# include <map>
# include <string>

class SyntacticAnalyzer
{
private:
    class BNFRule;
    class GrammarRule;

    static const std::vector<std::vector<std::string>> _grammar;
    std::map<std::string, BNFRule *> _grammarTree;
    BNFRule *_rootRule;

public:
    SyntacticAnalyzer();
    ~SyntacticAnalyzer();

    void *createTree(const std::vector<std::vector<Tokenizer::Token> *> &tokenizedFile);

private:
    bool _initGrammarMap();
    bool _initGrammarTree();
    bool _parseInput(const std::vector<std::vector<Tokenizer::Token> *> &tokenizedFile);
    // void _readCreatedGrammarTree(BNFRule *, int = 0);
};

#endif		// !SYNTACTIC_ANALYZER_HH_
