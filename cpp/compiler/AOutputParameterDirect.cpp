#include "AOutputParameterDirect.hh"
#include <iostream>

AOutput::ParameterDirect::ParameterDirect(ParserOutput::eType type, std::vector<ParserOutput::element *> *elements)
    : AOutput(type, elements), _isLabel(false)
{
}

AOutput::ParameterDirect::~ParameterDirect()
{
}

void AOutput::ParameterDirect::metamorhose()
{
    for (ParserOutput::element *element : *_elements)
    {
        if (element->token->raw() == ":")
            _isLabel = true;
        else if (element->token->raw() != "%")
        {
            if (_isLabel)
                _value.append(element->token->raw());
            else
                _value = element->token->raw();
        }
    }

    std::cout << "Metamorphosing direct parameter -> ";
    if (_isLabel)
        std::cout << "label: ";
    std::cout << _value << std::endl;
}

bool AOutput::ParameterDirect::isLabel() const
{
    return _isLabel;
}

const std::string &AOutput::ParameterDirect::value() const
{
    return _value;
}
