#ifndef		AOUTPUT_PARAMETER_DIRECT_HH_
# define	AOUTPUT_PARAMETER_DIRECT_HH_

# include "AOutput.hh"
# include "ParserOutput.hh"

class AOutput::ParameterDirect : public AOutput
{
    std::string _value;
    bool _isLabel;

public:
    ParameterDirect(ParserOutput::eType, std::vector<ParserOutput::element *> *);
    ~ParameterDirect();

    virtual void metamorhose();

    bool isLabel() const;
    const std::string &value() const;
};

#endif		// !AOUTPUT_PARAMETER_DIRECT_HH_
