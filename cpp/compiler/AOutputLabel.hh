#ifndef		AOUTPUT_LABEL_HH_
# define	AOUTPUT_LABEL_HH_

# include "AOutput.hh"
# include "ParserOutput.hh"

class AOutput::Label : public AOutput
{
    std::string _label;

public:
    Label(ParserOutput::eType, std::vector<ParserOutput::element *> *);
    ~Label();

    virtual void metamorhose();

    const std::string &name() const;
};

#endif		// !AOUTPUT_LABEL_HH_
