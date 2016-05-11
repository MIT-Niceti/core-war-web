#ifndef		AOUTPUT_PARAMETER_INDIRECT_HH_
# define	AOUTPUT_PARAMETER_INDIRECT_HH_

# include "AOutput.hh"
# include "ParserOutput.hh"

class AOutput::ParameterIndirect : public AOutput
{
    unsigned int _indirectValue;
    std::string _labelValue;

public:
    ParameterIndirect(ParserOutput::eType, std::vector<ParserOutput::element *> *);
    ~ParameterIndirect();

    virtual void metamorhose();

    bool isLabel() const;
    const std::string &labelValue() const;
    unsigned int numericValue() const;
};

#endif		// !AOUTPUT_PARAMETER_INDIRECT_HH_
