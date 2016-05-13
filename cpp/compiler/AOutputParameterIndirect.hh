#ifndef		AOUTPUT_PARAMETER_INDIRECT_HH_
# define	AOUTPUT_PARAMETER_INDIRECT_HH_

# include "AOutput.hh"
# include "ParserOutput.hh"

class AOutput::ParameterIndirect : public AOutput
{
    std::string _value;
    bool _isLabel;

public:
    ParameterIndirect(ParserOutput::eType, std::vector<ParserOutput::element *> *);
    ~ParameterIndirect();

    virtual void metamorhose();

    bool isLabel() const;
    const std::string &value() const;
};

#endif		// !AOUTPUT_PARAMETER_INDIRECT_HH_
