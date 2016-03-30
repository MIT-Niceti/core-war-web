#include "stdafx.h"
#include "Lfork.h"
#include "Arena.h"
#include "Process.h"

Lfork::Lfork()
{
	char firstArg[] = { DIRECT };

	this->name = "Lfork";
	this->opCode = 0x0F;
	this->cycle = 1000;
	this->paramByte = false;
	this->has_index = true;
	this->index[0] = true;
	this->index[1] = false;
	this->nbr_args = 1;
	this->types.push_back(std::vector<char>(firstArg, firstArg + sizeof(firstArg) / sizeof(char)));
}

bool Lfork::load(Process *caller, std::vector<Param> &params, Arena &arena)
{
	return true;
}

bool Lfork::execute(Process *caller, std::vector<Param> &params, Arena &arena)
{
	__int32 value1;

	value1 = InstructionFactory::getParamValue(params[0], arena, caller);
	caller->fork(caller->pc + value1);
	return true;
}


Lfork::~Lfork()
{
}
