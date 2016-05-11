#ifndef		AOUTPUT_INSTRUCTION_NAME_HH_
# define	AOUTPUT_INSTRUCTION_NAME_HH_

# include "AOutput.hh"
# include "ParserOutput.hh"

class AOutput::InstructionName : public AOutput
{
    std::string _name;

public:
    InstructionName(ParserOutput::eType, std::vector<ParserOutput::element *> *);
    ~InstructionName();

    virtual void metamorhose();

    const std::string &name() const;
};

#endif		// !AOUTPUT_INSTRUCTION_NAME_HH_
