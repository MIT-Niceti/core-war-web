#ifndef		AOUTPUT_PARAMETER_DIRECT_HH_
# define	AOUTPUT_PARAMETER_DIRECT_HH_

# include "AOutput.hh"
# include "ParserOutput.hh"

class AOutput::ParameterDirect : public AOutput
{
    unsigned int _directValue;
    std::string _labelValue;

public:
    ParameterDirect(ParserOutput::eType, std::vector<ParserOutput::element *> *);
    ~ParameterDirect();

    virtual void metamorhose();

    bool isLabel() const;
    const std::string &labelValue() const;
    unsigned int numericValue() const;
};

#endif		// !AOUTPUT_PARAMETER_DIRECT_HH_
