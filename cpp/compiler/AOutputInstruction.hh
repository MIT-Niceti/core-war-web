#ifndef		AOUTPUT_INSTRUCTION_HH_
# define	AOUTPUT_INSTRUCTION_HH_

# include "AOutput.hh"
# include "ParserOutput.hh"

class AOutput::Instruction : public AOutput
{
    std::vector<AOutput *> _parameters;
    InstructionName *_name;

public:
    Instruction(ParserOutput::eType, std::vector<ParserOutput::element *> *);
    ~Instruction();

    virtual void metamorhose();

    const std::string &name() const;
    const std::vector<AOutput *> &parameters() const;
};

#endif		// !AOUTPUT_INSTRUCTION_HH_
