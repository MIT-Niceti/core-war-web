#include "ChampionHeader.hh"
#include "Endianness.hh"
#include <iostream>

const std::vector<unsigned char> Champion::Header::header::magicNumber = { 0xB1, 0x6B, 0x00, 0xB5 };

Champion::Header::Header()
    : _hasName(false), _hasComment(false)
{
}

Champion::Header::~Header()
{
}

bool Champion::Header::write(std::ofstream &file)
{
    file.write((char *)(void *)_header.magicNumber.data(), _header.magicNumber.size());

    file.write(_header.name.data(), _header.name.size());

    _header.programSize = Endianness::toInt32BigEndian(_header.programSize);
    file.write((char *)(void *)&(_header.programSize), sizeof(_header.programSize));

    file.write(_header.comment.data(), _header.comment.size());
    return true;
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
    for (unsigned int i = 0; i != input->value().size(); ++i)
        _header.name[i] = input->value()[i];
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
    for (unsigned int i = 0; i != input->value().size(); ++i)
        _header.comment[i] = input->value()[i];
    _hasComment = true;
    return true;
}

void Champion::Header::setProgramSize(unsigned int size)
{
    _header.programSize = size;
}
