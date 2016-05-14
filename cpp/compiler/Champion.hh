#ifndef		CHAMPION_HH_
# define	CHAMPION_HH_

# include "AOutput.hh"
# include <fstream>
# include <vector>

class Champion
{
public:
    class Header;
    class Instruction;
    typedef Instruction Label;

private:
    Header *_header;
    std::vector<Instruction *> _instructions;
    std::vector<Label *> _labels;

public:
    Champion();
    ~Champion();

    bool translateMetaName(AOutput::MetaName *);
    bool translateMetaComment(AOutput::MetaComment *);
    bool translateLabel(AOutput::Label *);
    bool translateInstruction(AOutput::Instruction *);
    bool translateInstructionAndLabel(AOutput::InstructionAndLabel *);

    bool write(std::ofstream &);

    bool sortLabelsAndInstructions();
    bool computeLabelValues();
    bool computeProgramSize();

private:
    void _initHeader();
    bool _checkMultipleLabelDefinition();
    int _computeLabelJump(int, int);
    bool _writeInstructions(std::ofstream &);
};

#endif		// !CHAMPION_HH_
