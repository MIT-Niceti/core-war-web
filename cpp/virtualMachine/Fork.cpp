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

bool Fork::load(Process *caller, std::vector<Param> &params, Arena &arena)
{
	return true;
}

bool Fork::execute(Process *caller, std::vector<Param> &params, Arena &arena)
{
	int32_t value1;
	std::string test;

	value1 = InstructionFactory::getParamValue(params[0], arena, caller);
	arena.addEvent(caller->getParentId(), this->name, caller->parent->getHeader().prog_size, caller->pc + (value1 % IDX_MOD));
	caller->fork(caller->pc + (value1 % IDX_MOD), arena);
	return true;
}


Fork::~Fork()
{
}
