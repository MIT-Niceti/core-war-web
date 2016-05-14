#include "Endianness.hh"

Endianness::eEndian Endianness::_endian = Endianness::UNDEFINED;
uint16_t Endianness::_reference = 0x00FF;

void Endianness::_checkEndian()
{
    if (*((uint8_t *)&_reference) == 0x00)
        _endian = BIG;
    else if (*((uint8_t *)&_reference) == 0xFF)
        _endian = LITTLE;
    _endian = UNDEFINED;
}

Endianness::eEndian Endianness::endian()
{
    if (_endian == UNDEFINED)
        _checkEndian();
    return _endian;
}

uint16_t Endianness::toInt16BigEndian(uint16_t value)
{
    if (_endian == UNDEFINED)
        _checkEndian();
    return (_endian == BIG ? value : __builtin_bswap16(value));
}

uint32_t Endianness::toInt32BigEndian(uint32_t value)
{
    if (_endian == UNDEFINED)
        _checkEndian();
    return (_endian == BIG ? value : __builtin_bswap32(value));
}

uint64_t Endianness::toInt64BigEndian(uint64_t value)
{
    if (_endian == UNDEFINED)
        _checkEndian();
    return (_endian == BIG ? value : __builtin_bswap64(value));
}

uint16_t Endianness::toInt16LittleEndian(uint16_t value)
{
    if (_endian == UNDEFINED)
        _checkEndian();
    return (_endian == LITTLE ? value : __builtin_bswap16(value));
}

uint32_t Endianness::toInt32LittleEndian(uint32_t value)
{
    if (_endian == UNDEFINED)
        _checkEndian();
    return (_endian == LITTLE ? value : __builtin_bswap32(value));
}

uint64_t Endianness::toInt64LittleEndian(uint64_t value)
{
    if (_endian == UNDEFINED)
        _checkEndian();
    return (_endian == LITTLE ? value : __builtin_bswap64(value));
}
