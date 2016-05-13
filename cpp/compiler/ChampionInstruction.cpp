#include "ChampionInstruction.hh"
#include "ChampionInstructionOpCode.hh"
#include "ChampionInstructionParameters.hh"
#include <iostream>

const std::vector<Champion::Instruction::OpCode> Champion::Instruction::_possibleOpCodes =
{
    OpCode(OpCode::LIVE, "live"),
    OpCode(OpCode::LD, "ld"),
    OpCode(OpCode::ST, "st"),
    OpCode(OpCode::ADD, "add"),
    OpCode(OpCode::SUB, "sub"),
    OpCode(OpCode::AND, "and"),
    OpCode(OpCode::OR, "or"),
    OpCode(OpCode::XOR, "xor"),
    OpCode(OpCode::ZJMP, "zjmp"),
    OpCode(OpCode::LDI, "ldi"),
    OpCode(OpCode::STI, "sti"),
    OpCode(OpCode::FORK, "fork"),
    OpCode(OpCode::LLD, "lld"),
    OpCode(OpCode::LLDI, "lldi"),
    OpCode(OpCode::LFORK, "lfork"),
    OpCode(OpCode::PRINT, "print")
};

const std::vector<std::vector<Champion::Instruction::Parameters>> Champion::Instruction::_possibleParameters =
{
    std::vector<Parameters> { // LIVE
        Parameters(Parameter::DIRECT)
    },
    std::vector<Parameters> { // LD
        Parameters(Parameter::DIRECT, Parameter::INDIRECT),
        Parameters(Parameter::REGISTER)
    },
    std::vector<Parameters> { // ST
        Parameters(Parameter::REGISTER),
        Parameters(Parameter::REGISTER, Parameter::INDIRECT)
    },
    std::vector<Parameters> { // ADD
        Parameters(Parameter::REGISTER),
        Parameters(Parameter::REGISTER),
        Parameters(Parameter::REGISTER)
    },
    std::vector<Parameters> { // SUB
        Parameters(Parameter::REGISTER),
        Parameters(Parameter::REGISTER),
        Parameters(Parameter::REGISTER)
    },
    std::vector<Parameters> { // AND
        Parameters(Parameter::REGISTER, Parameter::DIRECT, Parameter::INDIRECT),
        Parameters(Parameter::REGISTER, Parameter::DIRECT, Parameter::INDIRECT),
        Parameters(Parameter::REGISTER)
    },
    std::vector<Parameters> { // OR
        Parameters(Parameter::REGISTER, Parameter::DIRECT, Parameter::INDIRECT),
        Parameters(Parameter::REGISTER, Parameter::DIRECT, Parameter::INDIRECT),
        Parameters(Parameter::REGISTER)
    },
    std::vector<Parameters> { // XOR
        Parameters(Parameter::REGISTER, Parameter::DIRECT, Parameter::INDIRECT),
        Parameters(Parameter::REGISTER, Parameter::DIRECT, Parameter::INDIRECT),
        Parameters(Parameter::REGISTER)
    },
    std::vector<Parameters> { // ZJUMP
        Parameters(Parameter::DIRECT)
    },
    std::vector<Parameters> { // LDI
        Parameters(Parameter::REGISTER, Parameter::DIRECT, Parameter::INDIRECT),
        Parameters(Parameter::REGISTER, Parameter::DIRECT),
        Parameters(Parameter::REGISTER)
    },
    std::vector<Parameters> { // STI
        Parameters(Parameter::REGISTER),
        Parameters(Parameter::REGISTER, Parameter::DIRECT, Parameter::INDIRECT),
        Parameters(Parameter::REGISTER, Parameter::DIRECT)
    },
    std::vector<Parameters> { // FORK
        Parameters(Parameter::DIRECT)
    },
    std::vector<Parameters> { // LLD
        Parameters(Parameter::DIRECT, Parameter::INDIRECT),
        Parameters(Parameter::REGISTER)
    },
    std::vector<Parameters> { // LLDI
        Parameters(Parameter::REGISTER, Parameter::DIRECT, Parameter::INDIRECT),
        Parameters(Parameter::REGISTER, Parameter::DIRECT),
        Parameters(Parameter::REGISTER)
    },
    std::vector<Parameters> { // LFORK
        Parameters(Parameter::DIRECT)
    },
    std::vector<Parameters> { // PRINT
        Parameters(Parameter::REGISTER)
    },
};

Champion::Instruction::Instruction()
    : _opCode(NULL)
{
}

Champion::Instruction::~Instruction()
{
}

bool Champion::Instruction::translate(AOutput::Label *input)
{
    _label = input->name();
    return true;
}

bool Champion::Instruction::hasLabel() const
{
    return !_label.empty();
}

bool Champion::Instruction::hasOpCode() const
{
    return _opCode;
}

const std::string &Champion::Instruction::labelName() const
{
    return _label;
}

unsigned int Champion::Instruction::size() const
{
    unsigned int size = sizeof(OpCode::eOpCode);

    for (Parameter *parameter : _parameters)
        size += parameter->size();
    return size;
}

const std::vector<Champion::Instruction::Parameter *> &Champion::Instruction::parameters() const
{
    return _parameters;
}

bool Champion::Instruction::translate(AOutput::Instruction *input)
{
    return _translateOpCode(input) && _translateParameters(input->parameters());
}

bool Champion::Instruction::_translateOpCode(AOutput::Instruction *input)
{
    OpCode::eOpCode opCode = OpCode::getOpCodeFromName(input->name());

    if (opCode == OpCode::INVALID)
    {
        std::cerr << "Error: Invalid op code '" << input->name() << "'" << std::endl;
        return false;
    }
    _opCode = new OpCode(opCode, input->name());
    return true;
}

bool Champion::Instruction::_translateParameters(const std::vector<AOutput *> &parameters)
{
    for (AOutput *inputParameter : parameters)
    {
        Parameter *parameter = new Parameter;

        if (!parameter->translate(inputParameter))
        {
            delete parameter;
            return false;
        }
        _parameters.push_back(parameter);
    }
    return true;
}

void Champion::Instruction::setOpCode(OpCode *opCode)
{
    _opCode = opCode;
}

Champion::Instruction::OpCode *Champion::Instruction::opCode()
{
    return _opCode;
}
