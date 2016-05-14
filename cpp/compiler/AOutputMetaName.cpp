#include "AOutputMetaName.hh"
#include <iostream>

AOutput::MetaName::MetaName(ParserOutput::eType type, std::vector<ParserOutput::element *> *elements)
    : AOutput(type, elements)
{
}

AOutput::MetaName::~MetaName()
{
}

void AOutput::MetaName::metamorhose()
{
    bool string = false;

    for (ParserOutput::element *element : *_elements)
    {
        if (element->token->raw() == "\"")
            string = true;
        if (string && element->token->raw() != "\"")
            _name.append(element->token->raw());
    }
    // std::cout << "Metamorphosing meta name -> \"" << _name << "\"" << std::endl;
}

const std::string &AOutput::MetaName::value() const
{
    return _name;
}
