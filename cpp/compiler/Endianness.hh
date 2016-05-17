#ifndef		ENDIANNESS_HH_
# define	ENDIANNESS_HH_

# include <cstdint>

# ifdef _WIN32
#  include <intrin.h>
#  define __builtin_bswap16 _byteswap_ushort
#  define __builtin_bswap32 _byteswap_ulong
#  define __builtin_bswap64 _byteswap_uint64
# endif // !_WIN32

class Endianness
{
private:
    enum eEndian
    {
        UNDEFINED,
        BIG,
        LITTLE
    };

    static eEndian _endian;
    static uint16_t _reference;

private:
    static void _checkEndian();

public:
    static eEndian endian();

    static uint16_t toInt16BigEndian(uint16_t);
    static uint32_t toInt32BigEndian(uint32_t);
    static uint64_t toInt64BigEndian(uint64_t);

    static uint16_t toInt16LittleEndian(uint16_t);
    static uint32_t toInt32LittleEndian(uint32_t);
    static uint64_t toInt64LittleEndian(uint64_t);
};

#endif		/* !ENDIANNESS_HH_ */
