#include "AOutputInstructionAndLabel.hh"
#include <iostream>

AOutput::InstructionAndLabel::InstructionAndLabel(ParserOutput::eType type, std::vector<ParserOutput::element *> *elements)
    : AOutput(type, elements)
{
}

AOutput::InstructionAndLabel::~InstructionAndLabel()
{
}

void AOutput::InstructionAndLabel::metamorhose()
{
    AOutput *element = _next;

    std::cout << "Metamorphosing instruction and label" << std::endl;
    while (element)
    {
        if (element->type() == ParserOutput::eType::INSTRUCTION)
        {
            _instruction = static_cast<Instruction *>(element);
            _instruction->metamorhose();
        }
        else if (element->type() == ParserOutput::eType::LABEL)
        {
            _label = static_cast<Label *>(element);
            _label->metamorhose();
        }
        element = element->_next;
    }
}
