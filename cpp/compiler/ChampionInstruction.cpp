#include "ChampionInstruction.hh"
#include "ChampionInstructionOpCode.hh"
#include "ChampionInstructionParameters.hh"
#include <iostream>
#include <cstdlib>

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
    std::vector<Parameters> {}, // Index 0, not used
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

const std::vector<bool> Champion::Instruction::_parametersEncodingByte =
{
    false, // Index 0, not used
    false, // LIVE
    true, // LD
    true, // ST
    false, // ADD
    false, // SUB
    true, // AND
    true, // OR
    true, // XOR
    false, // ZJMP
    true, // LDI
    true, //STI
    false, // FORK
    true, // LLD
    true, // LLDI
    false, // LFORK
    true // PRINT
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

    size = _parametersEncodingByte[_opCode->code()] ? size + 1 : size;
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
    return _translateOpCode(input) && _checkParameters(input->parameters()) && _translateParameters(input->parameters());
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
    unsigned int paramPos = 1;
    bool isIndex = false;

    for (AOutput *inputParameter : parameters)
    {
        Parameter *parameter = new Parameter;

        if (_opCode->code() == OpCode::FORK || _opCode->code() == OpCode::LFORK || _opCode->code() == OpCode::ZJMP ||
            (_opCode->code() == OpCode::STI && (paramPos == 2 || paramPos == 3)))
        {
            isIndex = true;
        }
        if (!parameter->translate(inputParameter, isIndex))
        {
            delete parameter;
            return false;
        }
        _parameters.push_back(parameter);
        isIndex = false;
        ++paramPos;
    }
    return true;
}

bool Champion::Instruction::_checkParameters(const std::vector<AOutput *> &parameters)
{
    const std::vector<Parameters> &possibleParametersForOperation = _possibleParameters[_opCode->code()];
    unsigned int paramPos = 1;
    bool isValid = false;

    for (unsigned int inputPositionIndex = 0; inputPositionIndex != parameters.size(); ++inputPositionIndex)
    {
        AOutput *inputParameter = parameters[inputPositionIndex];

        isValid = false;
        for (unsigned int possiblePositionIndex = 0; possiblePositionIndex != possibleParametersForOperation.size(); ++possiblePositionIndex)
        {
            if (inputPositionIndex == possiblePositionIndex)
            {
                for (unsigned int parametersTypePossibilitesIndex = 0; !isValid && possibleParametersForOperation[possiblePositionIndex][parametersTypePossibilitesIndex] != Parameter::INVALID; ++parametersTypePossibilitesIndex)
                {
                    if (inputParameter->type() == ParserOutput::REGISTER_PARAMETER && possibleParametersForOperation[possiblePositionIndex][parametersTypePossibilitesIndex] == Parameter::REGISTER)
                        isValid = true;
                    else if (inputParameter->type() == ParserOutput::DIRECT_PARAMETER && possibleParametersForOperation[possiblePositionIndex][parametersTypePossibilitesIndex] == Parameter::DIRECT)
                        isValid = true;
                    else if (inputParameter->type() == ParserOutput::INDIRECT_PARAMETER && possibleParametersForOperation[possiblePositionIndex][parametersTypePossibilitesIndex] == Parameter::INDIRECT)
                        isValid = true;
                }
                if (!isValid)
                {
                    std::cerr << "Error: Instruction '" << _opCode->name() << "' invalid parameter number " << paramPos << std::endl;
                    return false;
                }
            }
        }
        ++paramPos;
    }
    if ((paramPos - 1) > possibleParametersForOperation.size())
    {
        std::cerr << "Error: Instruction '" << _opCode->name() << "' has too much parameters " << std::endl;
        return false;
    }
    return true;
}

void Champion::Instruction::setOpCode(OpCode *opCode)
{
    _opCode = opCode;
}

void Champion::Instruction::setParameters(const std::vector<Parameter *> &parameters)
{
    _parameters = parameters;
}

Champion::Instruction::OpCode *Champion::Instruction::opCode()
{
    return _opCode;
}

bool Champion::Instruction::write(std::ofstream &file)
{
    Instruction::OpCode::eOpCode opCode = _opCode->code();

    file.write((char *)&opCode, sizeof(opCode));
    if (!_writeParametersEncodingByte(file))
        return false;
    for (Parameter *parameter : _parameters)
        parameter->write(file);
    return true;
}

bool Champion::Instruction::_writeParametersEncodingByte(std::ofstream &file)
{
    std::string binaryString;
    char parametersByte = 0;

    if (!_parametersEncodingByte[_opCode->code()])
        return true;
    for (Parameter *parameter : _parameters)
    {
        if (parameter->type() == Parameter::REGISTER)
            binaryString += "01";
        else if (parameter->type() == Parameter::DIRECT)
            binaryString += "10";
        else if (parameter->type() == Parameter::INDIRECT)
            binaryString += "11";
    }
    while (binaryString.size() != 8)
        binaryString.push_back('0');
    parametersByte = strtol(binaryString.c_str(), NULL, 2);
    file.write((char *)&parametersByte, sizeof(parametersByte));
    return true;
}
