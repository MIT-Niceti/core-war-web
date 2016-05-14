#include "AOutputParameterRegister.hh"
#include <sstream>
#include <iostream>

AOutput::ParameterRegister::ParameterRegister(ParserOutput::eType type, std::vector<ParserOutput::element *> *elements)
    : AOutput(type, elements)
{
}

AOutput::ParameterRegister::~ParameterRegister()
{
}

void AOutput::ParameterRegister::metamorhose()
{
    _register = (*_elements)[1]->token->raw();
    // std::cout << "Metamorphosing parameter register -> r" << _register << std::endl;
}

const std::string &AOutput::ParameterRegister::registerNumber() const
{
    return _register;
}
