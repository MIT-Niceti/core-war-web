#ifndef		AOUTPUT_META_NAME_HH_
# define	AOUTPUT_META_NAME_HH_

# include "AOutput.hh"
# include "ParserOutput.hh"

class AOutput::MetaName : public AOutput
{
    std::string _name;

public:
    MetaName(ParserOutput::eType, std::vector<ParserOutput::element *> *);
    ~MetaName();

    virtual void metamorhose();

    const std::string &name() const;
};

#endif		// !AOUTPUT_META_NAME_HH_
