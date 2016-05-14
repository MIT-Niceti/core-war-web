#include "AOutputMetaComment.hh"
#include <iostream>

AOutput::MetaComment::MetaComment(ParserOutput::eType type, std::vector<ParserOutput::element *> *elements)
    : AOutput(type, elements)
{
}

AOutput::MetaComment::~MetaComment()
{
}

void AOutput::MetaComment::metamorhose()
{
    bool string = false;

    for (ParserOutput::element *element : *_elements)
    {
        if (element->token->raw() == "\"")
            string = true;
        if (string && element->token->raw() != "\"")
            _comment.append(element->token->raw());
    }
    // std::cout << "Metamorphosing meta comment -> \"" << _comment << "\"" << std::endl;
}

const std::string &AOutput::MetaComment::value() const
{
    return _comment;
}
