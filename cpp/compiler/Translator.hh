#ifndef		TRANSLATOR_HH_
# define	TRANSLATOR_HH_

# include "SyntacticAnalyzer.hh"
# include "Champion.hh"

class Translator
{
private:
    Champion _translated;

public:
    Translator();
    ~Translator();

    bool translate(ParsedLines *);
    bool write();

private:
    bool _fillOutputStructure(ParsedLines *);
};

#endif		// !TRANSLATOR_HH_
