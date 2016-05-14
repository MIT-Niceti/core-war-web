#include "ChampionInstructionParameter.hh"
#include "Endianness.hh"
#include <sstream>
#include <iostream>

Champion::Instruction::Parameter::Parameter()
    : _type(INVALID), _isIndex(false)
{
}

Champion::Instruction::Parameter::~Parameter()
{
}

bool Champion::Instruction::Parameter::translate(AOutput *parameter, bool isIndex)
{
    _isIndex = isIndex;
    if (parameter->type() == ParserOutput::REGISTER_PARAMETER)
        return _translateRegisterParameter(static_cast<AOutput::ParameterRegister *>(parameter));
    else if (parameter->type() == ParserOutput::DIRECT_PARAMETER)
        return _translateDirectParameter(static_cast<AOutput::ParameterDirect *>(parameter));
    else if (parameter->type() == ParserOutput::INDIRECT_PARAMETER)
        return _translateIndirectParameter(static_cast<AOutput::ParameterIndirect *>(parameter));
    return false;
}

void Champion::Instruction::Parameter::setDirectValue(int32_t value)
{
    _directValue = value;
}

void Champion::Instruction::Parameter::setIndirectValue(int16_t value)
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
    if (_type == REGISTER && !_isIndex)
        return sizeof(_registerNumber);
    else if (_type == DIRECT && !_isIndex)
        return sizeof(_directValue);
    else if (_type == INDIRECT || _isIndex)
        return sizeof(_indirectValue);
    return 0;
}

bool Champion::Instruction::Parameter::isIndex() const
{
    return _isIndex;
}

bool Champion::Instruction::Parameter::write(std::ofstream &file)
{
    if (_type == REGISTER && !_isIndex)
        file.write((char *)&_registerNumber, sizeof(_registerNumber));
    else if (_type == DIRECT && !_isIndex)
    {
        int32_t value = Endianness::toInt32BigEndian(_directValue);

        file.write((char *)(void *)&value, sizeof(_directValue));
    }
    else if (_type == INDIRECT && !_isIndex)
    {
        int16_t value = Endianness::toInt16BigEndian(_indirectValue);

        file.write((char *)(void *)&value, sizeof(_indirectValue));
    }
    else if (_isIndex)
    {
        int16_t indexValue = 0;

        if (_type == REGISTER)
            indexValue = _registerNumber;
        else if (_type == DIRECT)
            indexValue = _directValue;
        else if (_type == INDIRECT)
            indexValue = _indirectValue;
        indexValue = Endianness::toInt16BigEndian(indexValue);
        file.write((char *)(void *)&indexValue, sizeof(indexValue));
    }
    return true;
}
