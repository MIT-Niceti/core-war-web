#ifndef		CHAMPION_INSTRUCTION_HH_
# define	CHAMPION_INSTRUCTION_HH_

# include "Champion.hh"
# include "AOutput.hh"
# include <string>
# include <vector>

class Champion::Instruction
{
public:
    class Parameter;
    class Parameters;
    class OpCode;

private:
    static const std::vector<OpCode> _possibleOpCodes;
    static const std::vector<std::vector<Parameters>> _possibleParameters;

    std::string _label;
    OpCode *_opCode;
    std::vector<Parameter *> _parameters;

public:
    Instruction();
    ~Instruction();

    bool translate(AOutput::Label *);
    bool translate(AOutput::Instruction *);

    void setOpCode(OpCode *);

    bool hasLabel() const;
    bool hasOpCode() const;
    const std::string &labelName() const;
    unsigned int size() const;
    const std::vector<Parameter *> &parameters() const;

    OpCode *opCode();

private:
    bool _translateOpCode(AOutput::Instruction *);
    bool _translateParameters(const std::vector<AOutput *> &);
};

#endif		// !CHAMPION_INSTRUCTION_HH_
