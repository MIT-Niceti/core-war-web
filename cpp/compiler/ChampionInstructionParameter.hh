#ifndef		CHAMPION_INSTRUCTION_PARAMETER_HH_
# define	CHAMPION_INSTRUCTION_PARAMETER_HH_

# include "ChampionInstruction.hh"
# include <string>

class Champion::Instruction::Parameter
{
public:
    enum eType
    {
        INVALID = 0,
        REGISTER,
        DIRECT,
        INDIRECT
    };

private:
    eType _type;
    char _registerNumber;
    int _directValue;
    short _indirectValue;
    std::string _label;

public:
    Parameter();
    ~Parameter();

    bool translate(AOutput *);

    void setDirectValue(int);
    void setIndirectValue(short);

    eType type() const;
    bool isLabel() const;
    const std::string &label() const;
    unsigned int size() const;

    bool _translateRegisterParameter(AOutput::ParameterRegister *);
    bool _translateDirectParameter(AOutput::ParameterDirect *);
    bool _translateIndirectParameter(AOutput::ParameterIndirect *);
};

#endif		// !CHAMPION_INSTRUCTION_PARAMETER_HH_
