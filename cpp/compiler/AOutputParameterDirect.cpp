#include "AOutputParameterDirect.hh"
#include <sstream>
#include <iostream>

AOutput::ParameterDirect::ParameterDirect(ParserOutput::eType type, std::vector<ParserOutput::element *> *elements)
    : AOutput(type, elements)
{
}

AOutput::ParameterDirect::~ParameterDirect()
{
}

void AOutput::ParameterDirect::metamorhose()
{
    bool labelValue = false;
    std::string value;

    for (ParserOutput::element *element : *_elements)
    {
        if (element->token->raw() == ":")
            labelValue = true;
        else if (element->token->raw() != "%")
        {
            if (labelValue)
                value.append(element->token->raw());
            else
                value = element->token->raw();
        }
    }

    if (labelValue)
        _labelValue = value;
    else
    {
        std::istringstream convert(value);
        convert >> _directValue;
    }

    std::cout << "Metamorphosing parameter direct -> ";
    if (_labelValue.size())
        std::cout << "label: " << _labelValue << std::endl;
    else
        std::cout << _directValue << std::endl;
}
