#ifndef		AOUTPUT_PARAMETER_REGISTER_HH_
# define	AOUTPUT_PARAMETER_REGISTER_HH_

# include "AOutput.hh"
# include "ParserOutput.hh"

class AOutput::ParameterRegister : public AOutput
{
private:
    std::string _register;

public:
    ParameterRegister(ParserOutput::eType, std::vector<ParserOutput::element *> *);
    ~ParameterRegister();

    virtual void metamorhose();

    const std::string &registerNumber() const;
};

#endif		// !AOUTPUT_PARAMETER_REGISTER_HH_
