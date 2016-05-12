#ifndef		AOUTPUT_META_COMMENT_HH_
# define	AOUTPUT_META_COMMENT_HH_

# include "AOutput.hh"
# include "ParserOutput.hh"

class AOutput::MetaComment : public AOutput
{
    std::string _comment;

public:
    MetaComment(ParserOutput::eType, std::vector<ParserOutput::element *> *);
    ~MetaComment();

    virtual void metamorhose();

    const std::string &value() const;
};

#endif		// !AOUTPUT_META_COMMENT_HH_
