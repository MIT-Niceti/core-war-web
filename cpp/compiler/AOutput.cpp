#include "AOutput.hh"
#include "AOutputMetaName.hh"
#include <iostream>

AOutput::AOutput(ParserOutput::eType type, std::vector<ParserOutput::element *> *elements)
    : _type(type), _elements(elements), _prev(NULL), _next(NULL)
{
}

AOutput::~AOutput()
{
}

void AOutput::print()
{
    std::cout << "Valid block | type: " << _type << " =>";
    for (ParserOutput::element *ruleElem : *_elements)
    {
        std::cout << " [" << ruleElem->token->raw() << "]";
    }
    std::cout << std::endl;
}

void AOutput::setPrev(AOutput *prev)
{
    _prev = prev;
}

void AOutput::setNext(AOutput *next)
{
    _next = next;
}

AOutput *AOutput::prev()
{
    return _prev;
}

AOutput *AOutput::next()
{
    return _next;
}

ParserOutput::eType AOutput::type() const
{
    return _type;
}

unsigned int AOutput::iStart() const
{
    return _elements->front()->i;
}

unsigned int AOutput::iEnd() const
{
    return _elements->back()->i;
}
