#include "ChampionHeader.hh"
#include <iostream>

Champion::Header::Header()
    : _hasName(false), _hasComment(false)
{
}

Champion::Header::~Header()
{
}

bool Champion::Header::setName(AOutput::MetaName *input)
{
    if (_hasName)
    {
        std::cerr << "Error: Multiple '.name' declaration" << std::endl;
        return false;
    }
    if (input->value().size() > _header.name.size() - 1)
    {
        std::cerr << "Error: '.name' string size exceeeds " << (_header.name.size() - 1) << " characters" << std::endl;
        return false;
    }
    for (char c : input->value())
        _header.name.push_back(c);
    _hasName = true;
    return true;
}

bool Champion::Header::setComment(AOutput::MetaComment *input)
{
    if (_hasComment)
    {
        std::cerr << "Error: Multiple '.comment' declaration" << std::endl;
        return false;
    }
    if (input->value().size() > _header.comment.size() - 1)
    {
        std::cerr << "Error: '.comment' string size exceeeds " << (_header.name.size() - 1) << " characters" << std::endl;
        return false;
    }
    for (char c : input->value())
        _header.comment.push_back(c);
    _hasComment = true;
    return true;
}
