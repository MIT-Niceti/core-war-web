#ifndef		AOUTPUT_PARAMETER_REGISTER_HH_
# define	AOUTPUT_PARAMETER_REGISTER_HH_

# include "AOutput.hh"
# include "ParserOutput.hh"

class AOutput::ParameterRegister : public AOutput
{
private:
    unsigned int _register;

public:
    ParameterRegister(ParserOutput::eType, std::vector<ParserOutput::element *> *);
    ~ParameterRegister();

    virtual void metamorhose();

    unsigned int registerNumber() const;
};

#endif		// !AOUTPUT_PARAMETER_REGISTER_HH_
