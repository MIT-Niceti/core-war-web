#include "AOutputParameterIndirect.hh"
#include <sstream>
#include <iostream>

AOutput::ParameterIndirect::ParameterIndirect(ParserOutput::eType type, std::vector<ParserOutput::element *> *elements)
    : AOutput(type, elements)
{
}

AOutput::ParameterIndirect::~ParameterIndirect()
{
}

void AOutput::ParameterIndirect::metamorhose()
{
    bool labelValue = false;
    std::string value;

    for (ParserOutput::element *element : *_elements)
    {
        if (element->token->raw() == ":")
            labelValue = true;
        else
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
        convert >> _indirectValue;
    }

    std::cout << "Metamorphosing parameter indirect -> ";
    if (_labelValue.size())
        std::cout << "label: " << _labelValue << std::endl;
    else
        std::cout << _indirectValue << std::endl;
}
