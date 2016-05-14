#ifndef		CHAMPION_INSTRUCTION_OP_CODE_HH_
# define	CHAMPION_INSTRUCTION_OP_CODE_HH_

# include "ChampionInstruction.hh"
# include <string>

class Champion::Instruction::OpCode
{
public:
    enum eOpCode : char
    {
        LIVE    = 0x01,
        LD      = 0x02,
        ST      = 0x03,
        ADD     = 0x04,
        SUB     = 0x05,
        AND     = 0x06,
        OR      = 0x07,
        XOR     = 0x08,
        ZJMP    = 0x09,
        LDI     = 0x0A,
        STI     = 0x0B,
        FORK    = 0x0C,
        LLD     = 0x0D,
        LLDI    = 0x0E,
        LFORK   = 0x0F,
        PRINT   = 0x10,
        INVALID = 0x42
    };

private:
    eOpCode _opCode;
    std::string _name;

public:
    OpCode(eOpCode, const std::string &);
    ~OpCode();

    const std::string &name() const;
    eOpCode code() const;

    static eOpCode getOpCodeFromName(const std::string &);
};

#endif		// !CHAMPION_INSTRUCTION_OP_CODE_HH_
