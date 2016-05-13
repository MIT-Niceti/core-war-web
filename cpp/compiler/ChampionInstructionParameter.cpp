#include "ChampionInstructionParameter.hh"
#include <sstream>
#include <iostream>

Champion::Instruction::Parameter::Parameter()
    : _type(INVALID)
{
}

Champion::Instruction::Parameter::~Parameter()
{
}

bool Champion::Instruction::Parameter::translate(AOutput *parameter)
{
    if (parameter->type() == ParserOutput::REGISTER_PARAMETER)
        return _translateRegisterParameter(static_cast<AOutput::ParameterRegister *>(parameter));
    else if (parameter->type() == ParserOutput::DIRECT_PARAMETER)
        return _translateDirectParameter(static_cast<AOutput::ParameterDirect *>(parameter));
    else if (parameter->type() == ParserOutput::INDIRECT_PARAMETER)
        return _translateIndirectParameter(static_cast<AOutput::ParameterIndirect *>(parameter));
    return false;
}

void Champion::Instruction::Parameter::setDirectValue(int value)
{
    _directValue = value;
}

void Champion::Instruction::Parameter::setIndirectValue(short value)
{
    _indirectValue = value;
}

bool Champion::Instruction::Parameter::_translateRegisterParameter(AOutput::ParameterRegister *parameter)
{
    std::istringstream convert(parameter->registerNumber());
    int registerNumber = -1;

    if (parameter->registerNumber().size() > 2 || !(convert >> registerNumber) || registerNumber < 1 || registerNumber > 16)
    {
        std::cerr << "Error: Invalid register number r" << parameter->registerNumber() << std::endl;
        return false;
    }
    _registerNumber = registerNumber;
    _type = REGISTER;
    return true;
}

bool Champion::Instruction::Parameter::_translateDirectParameter(AOutput::ParameterDirect *parameter)
{
    if (parameter->isLabel())
    {
        _label = parameter->value();
        _type = DIRECT;
        return true;
    }

    std::istringstream convert(parameter->value());

    if (!(convert >> _directValue))
    {
        std::cerr << "Error: Invalid direct value " << parameter->value() << std::endl;
        return false;
    }
    _type = DIRECT;
    return true;
}

bool Champion::Instruction::Parameter::_translateIndirectParameter(AOutput::ParameterIndirect *parameter)
{
    if (parameter->isLabel())
    {
        _label = parameter->value();
        _type = INDIRECT;
        return true;
    }

    std::istringstream convert(parameter->value());

    if (!(convert >> _indirectValue))
    {
        std::cerr << "Error: Invalid indirect value " << parameter->value() << std::endl;
        return false;
    }
    _type = INDIRECT;
    return true;
}

Champion::Instruction::Parameter::eType Champion::Instruction::Parameter::type() const
{
    return _type;
}

bool Champion::Instruction::Parameter::isLabel() const
{
    return _label.size();
}

const std::string &Champion::Instruction::Parameter::label() const
{
    return _label;
}

unsigned int Champion::Instruction::Parameter::size() const
{
    if (_type == REGISTER)
        return sizeof(_registerNumber);
    else if (_type == DIRECT)
        return sizeof(_directValue);
    else if (_type == INDIRECT)
        return sizeof(_indirectValue);
    return 0;
}
