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
    std::istringstream convert((*_elements)[1]->token->raw());

    convert >> _register;
    std::cout << "Metamorphosing parameter register -> r" << _register << std::endl;
}
