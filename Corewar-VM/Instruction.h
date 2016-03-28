#pragma once

#include "Param.h"
#include "Op.h"

class Process;

class Instruction
{
private:
	std::vector<Param>	params;
	Process				*caller;

public:
	Op					*op;

	bool exec(Arena &arena);
	Instruction(Op *op, std::vector<Param> params, Process *caller);
	~Instruction();
};

