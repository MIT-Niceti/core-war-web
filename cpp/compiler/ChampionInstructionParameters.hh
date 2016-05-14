#ifndef		CHAMPION_INSTRUCTION_PARAMETERS_HH_
# define	CHAMPION_INSTRUCTION_PARAMETERS_HH_

# include "ChampionInstruction.hh"
# include "ChampionInstructionParameter.hh"
# include <vector>

class Champion::Instruction::Parameters
{
private:
    std::vector<Parameter::eType> _parametersTypes;

public:
    Parameters(Parameter::eType, Parameter::eType = Parameter::INVALID, Parameter::eType = Parameter::INVALID);
    ~Parameters();

    Parameter::eType operator[](unsigned int) const;
};

#endif		// !CHAMPION_INSTRUCTION_PARAMETERS_HH_
