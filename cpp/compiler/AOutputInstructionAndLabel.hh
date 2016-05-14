#ifndef		AOUTPUT_INSTRUCTION_AND_LABEL_HH_
# define	AOUTPUT_INSTRUCTION_AND_LABEL_HH_

# include "AOutput.hh"
# include "ParserOutput.hh"

class AOutput::InstructionAndLabel : public AOutput
{
    Label *_label;
    Instruction *_instruction;

public:
    InstructionAndLabel(ParserOutput::eType, std::vector<ParserOutput::element *> *);
    ~InstructionAndLabel();

    virtual void metamorhose();

    Label *label();
    Instruction *instruction();
};

#endif		// !AOUTPUT_INSTRUCTION_AND_LABEL_HH_
