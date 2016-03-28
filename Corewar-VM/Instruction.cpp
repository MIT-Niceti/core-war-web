#include "stdafx.h"
#include "Instruction.h"
#include "Process.h"
#include "Arena.h"


bool Instruction::exec(Arena &arena)
{
	return this->op->execute(this->caller, this->params, arena);
}

Instruction::Instruction(Op *op, std::vector<Param> params, Process *caller)
{
	this->op = op;
	this->params = params;
	this->caller = caller;
}


Instruction::~Instruction()
{
}
