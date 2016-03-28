#include "stdafx.h"
#include "Fork.h"
#include "Process.h"
#include "Arena.h"

Fork::Fork()
{
	char firstArg[] = { DIRECT };

	this->name = "Fork";
	this->opCode = 0x0C;
	this->cycle = 800;
	this->paramByte = false;
	this->nbr_args = 1;
	this->has_index = true;
	this->index[0] = true;
	this->index[1] = false;
	this->index[3] = false;
	this->types.push_back(std::vector<char>(firstArg, firstArg + sizeof(firstArg) / sizeof(char)));
}

bool Fork::execute(Process *caller, std::vector<Param> &params, Arena &arena)
{
	__int32 value1;

	value1 = InstructionFactory::getParamValue(params[0], arena, caller);
	caller->fork(caller->pc + (value1 % IDX_MOD));
	return true;
}


Fork::~Fork()
{
}
