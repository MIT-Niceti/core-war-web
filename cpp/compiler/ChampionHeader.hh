#ifndef		CHAMPION_HEADER_HH_
# define	CHAMPION_HEADER_HH_

# include "Champion.hh"

class Champion::Header
{
private:
    struct header
    {
        const std::vector<unsigned char> magicNumber = { 0xB1, 0x6B, 0x00, 0xB5 };
        std::vector<char> name = std::vector<char>(128, '\0');
        unsigned int programSize = 0;
        std::vector<char> comment = std::vector<char>(2048, '\0');
    };

    header _header;
    bool _hasName;
    bool _hasComment;

public:
    Header();
    ~Header();

    bool write(std::ofstream &);

    bool setName(AOutput::MetaName *);
    bool setComment(AOutput::MetaComment *);
    void setProgramSize(unsigned int);
};

#endif		// !CHAMPION_HEADER_HH_
