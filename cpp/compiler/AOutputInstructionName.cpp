#include "AOutputInstructionName.hh"
#include <iostream>

AOutput::InstructionName::InstructionName(ParserOutput::eType type, std::vector<ParserOutput::element *> *elements)
    : AOutput(type, elements)
{
}

AOutput::InstructionName::~InstructionName()
{
}

void AOutput::InstructionName::metamorhose()
{
    _name = _elements->front()->token->raw();
    std::cout << "Metamorphosing instruction name -> " << _name << std::endl;
}
