#include "stdafx.h"
#include "Sti.h"
#include "Process.h"
#include "Arena.h"

Sti::Sti()
{
	char firstArg[] = { REGISTER };
	char secondArg[] = { REGISTER, DIRECT, INDIRECT };
	char thirdArg[] = { REGISTER, DIRECT };

	this->name = "Sti";
	this->opCode = 0x0B;
	this->cycle = 25;
	this->nbr_args = 3;
	this->has_index = true;
	this->index[0] = false;
	this->index[1] = true;
	this->index[2] = true;
	this->index[3] = false;
	this->types.push_back(std::vector<char>(firstArg, firstArg + sizeof(firstArg) / sizeof(char)));
	this->types.push_back(std::vector<char>(secondArg, secondArg + sizeof(secondArg) / sizeof(char)));
	this->types.push_back(std::vector<char>(thirdArg, thirdArg + sizeof(thirdArg) / sizeof(char)));
}

bool Sti::load(Process *caller, std::vector<Param> &params, Arena &arena)
{
	caller->values[0] = InstructionFactory::getParamValue(params[0], arena, caller);
	caller->values[1] = InstructionFactory::getParamValue(params[1], arena, caller);
	caller->values[2] = InstructionFactory::getParamValue(params[2], arena, caller);
	return true;
}

bool Sti::execute(Process *caller, std::vector<Param> &params, Arena &arena)
{
	std::vector<char>	data;

	data.push_back(caller->values[0]);
	arena.load(caller->pc + ((caller->values[1] + caller->values[2]) % IDX_MOD), data);
	return true;
}

Sti::~Sti()
{
}
