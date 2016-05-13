#include "ChampionInstructionOpCode.hh"

Champion::Instruction::OpCode::OpCode(eOpCode opCode, const std::string &name)
    : _opCode(opCode), _name(name)
{
}

Champion::Instruction::OpCode::~OpCode()
{
}

const std::string &Champion::Instruction::OpCode::name() const
{
    return _name;
}

Champion::Instruction::OpCode::eOpCode Champion::Instruction::OpCode::code() const
{
    return _opCode;
}

Champion::Instruction::OpCode::eOpCode Champion::Instruction::OpCode::getOpCodeFromName(const std::string &name)
{
    OpCode::eOpCode opCode = INVALID;
    unsigned int i = 0;

    while (i != Champion::Instruction::_possibleOpCodes.size())
    {
        if (_possibleOpCodes[i].name() == name)
        {
            opCode = static_cast<OpCode::eOpCode>(i);
            break ;
        }
        ++i;
    }
    return opCode;
}
