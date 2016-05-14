#include "ChampionInstructionParameters.hh"

Champion::Instruction::Parameters::Parameters(Parameter::eType param1, Parameter::eType param2, Parameter::eType param3)
{
    _parametersTypes.push_back(param1);
    if (param2 != Parameter::INVALID)
        _parametersTypes.push_back(param2);
    if (param3 != Parameter::INVALID)
        _parametersTypes.push_back(param3);
}

Champion::Instruction::Parameters::~Parameters()
{
}

Champion::Instruction::Parameter::eType Champion::Instruction::Parameters::operator[](unsigned int paramPos) const
{
    return paramPos < _parametersTypes.size() ? _parametersTypes[paramPos] : Parameter::eType::INVALID;
}
