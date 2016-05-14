#ifndef		PARSER_OUTPUT_HH_
# define	PARSER_OUTPUT_HH_

# include "Token.hh"
# include <vector>

class AOutput;

class ParserOutput
{
public:
    enum eType
    {
        INVALID = 0,

        // Valid alone
        META_NAME,
        META_COMMENT,
        INSTRUCTION,
        LABEL,
        INSTRUCTION_AND_LABEL,

        // Invalid alone
        INSTRUCTION_NAME,
        REGISTER_PARAMETER,
        DIRECT_PARAMETER,
        INDIRECT_PARAMETER,
    };

    struct element
    {
        const Token *token;
        unsigned int i;
        eType type;

        element() : token(NULL), i(0), type(eType::INVALID) {}
        element(const Token *token_, unsigned int i_) : token(token_), i(i_), type(eType::INVALID) {}
    };

private:
    std::vector<element *> _input;
    std::vector<AOutput *> _output;

public:
    ParserOutput();
    ~ParserOutput();

    void addElement(const Token *, unsigned int);
    void constructOutput(const std::string &, unsigned int, unsigned int);
    AOutput *finalizeOutput();

private:
    AOutput *_createRuleOutput(eType, std::vector<element *> *);
    eType _getRuleTypeFromRuleName(const std::string &) const;
};

#endif		// !PARSER_OUTPUT_HH_
