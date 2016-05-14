#ifndef		CHAMPION_INSTRUCTION_PARAMETER_HH_
# define	CHAMPION_INSTRUCTION_PARAMETER_HH_

# include "ChampionInstruction.hh"
# include <cstdint>
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
    int8_t _registerNumber;
    int32_t _directValue;
    int16_t _indirectValue;
    std::string _label;
    bool _isIndex;

public:
    Parameter();
    ~Parameter();

    bool translate(AOutput *, bool);

    void setDirectValue(int32_t);
    void setIndirectValue(int16_t);

    eType type() const;
    bool isLabel() const;
    const std::string &label() const;
    unsigned int size() const;
    bool isIndex() const;

    bool write(std::ofstream &);

private:
    bool _translateRegisterParameter(AOutput::ParameterRegister *);
    bool _translateDirectParameter(AOutput::ParameterDirect *);
    bool _translateIndirectParameter(AOutput::ParameterIndirect *);
};

#endif		// !CHAMPION_INSTRUCTION_PARAMETER_HH_
