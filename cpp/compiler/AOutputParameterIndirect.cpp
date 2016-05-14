#include "AOutputParameterIndirect.hh"
#include <iostream>

AOutput::ParameterIndirect::ParameterIndirect(ParserOutput::eType type, std::vector<ParserOutput::element *> *elements)
    : AOutput(type, elements), _isLabel(false)
{
}

AOutput::ParameterIndirect::~ParameterIndirect()
{
}

void AOutput::ParameterIndirect::metamorhose()
{
    for (ParserOutput::element *element : *_elements)
    {
        if (element->token->raw() == ":")
            _isLabel = true;
        else
        {
            if (_isLabel)
                _value.append(element->token->raw());
            else
                _value = element->token->raw();
        }
    }

    // std::cout << "Metamorphosing indirect parameter -> ";
    // if (_isLabel)
    //     std::cout << "label: ";
    // std::cout << _value << std::endl;
}

bool AOutput::ParameterIndirect::isLabel() const
{
    return _isLabel;
}

const std::string &AOutput::ParameterIndirect::value() const
{
    return _value;
}
