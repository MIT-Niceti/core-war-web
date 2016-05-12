#include "AOutputLabel.hh"
#include <iostream>

AOutput::Label::Label(ParserOutput::eType type, std::vector<ParserOutput::element *> *elements)
    : AOutput(type, elements)
{
}

AOutput::Label::~Label()
{
}

void AOutput::Label::metamorhose()
{
    for (ParserOutput::element *element : *_elements)
    {
        if (element->token->raw() != ":")
        {
            _label.append(element->token->raw());
        }
    }
    std::cout << "Metamorphosing label -> " << _label << std::endl;
}

const std::string &AOutput::Label::name() const
{
    return _label;
}
