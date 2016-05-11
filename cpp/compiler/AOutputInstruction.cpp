#include "AOutputInstruction.hh"
#include <iostream>

AOutput::Instruction::Instruction(ParserOutput::eType type, std::vector<ParserOutput::element *> *elements)
    : AOutput(type, elements)
{
}

AOutput::Instruction::~Instruction()
{
}

void AOutput::Instruction::metamorhose()
{
    AOutput *element = _next;

    std::cout << "Metamorphosing instruction" << std::endl;
    while (element && element->_next)
        element = element->_next;
    while (element)
    {
        if (element->type() == ParserOutput::eType::INSTRUCTION_NAME)
        {
            _name = static_cast<InstructionName *>(element);
            _name->metamorhose();
        }
        else if (element->type() == ParserOutput::eType::REGISTER_PARAMETER)
        {
            static_cast<ParameterRegister *>(element)->metamorhose();
            _parameters.push_back(element);
        }
        else if (element->type() == ParserOutput::eType::DIRECT_PARAMETER)
        {
            static_cast<ParameterDirect *>(element)->metamorhose();
            _parameters.push_back(element);
        }
        else if (element->type() == ParserOutput::eType::INDIRECT_PARAMETER)
        {
            static_cast<ParameterIndirect *>(element)->metamorhose();
            _parameters.push_back(element);
        }

        element = element->_prev;
    }
}
