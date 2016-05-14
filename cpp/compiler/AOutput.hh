#ifndef		AOUTPUT_HH_
# define	AOUTPUT_HH_

# include "ParserOutput.hh"

class AOutput
{
public:
    class MetaName;
    class MetaComment;
    class Instruction;
    class Label;
    class InstructionAndLabel;
    class InstructionName;
    class ParameterRegister;
    class ParameterDirect;
    class ParameterIndirect;

protected:
    const ParserOutput::eType _type;
    std::vector<ParserOutput::element *> *_elements;

private:
    AOutput *_prev;
    AOutput *_next;

public:
    AOutput(ParserOutput::eType, std::vector<ParserOutput::element *> *);
    virtual ~AOutput();

    virtual void metamorhose() = 0;
    void print();

    void setPrev(AOutput *);
    void setNext(AOutput *);

    ParserOutput::eType type() const;
    unsigned int iStart() const;
    unsigned int iEnd() const;

    AOutput *prev();
    AOutput *next();
};

# include "AOutputMetaName.hh"
# include "AOutputMetaComment.hh"
# include "AOutputInstruction.hh"
# include "AOutputLabel.hh"
# include "AOutputInstructionAndLabel.hh"
# include "AOutputInstructionName.hh"
# include "AOutputParameterRegister.hh"
# include "AOutputParameterDirect.hh"
# include "AOutputParameterIndirect.hh"

#endif		// !AOUTPUT_HH_
