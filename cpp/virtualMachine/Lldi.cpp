#include "stdafx.h"
#include "Lldi.h"
#include "Arena.h"
#include "Process.h"

Lldi::Lldi()
{
	char firstArg[] = { REGISTER, DIRECT, INDIRECT };
	char secondArg[] = { DIRECT, REGISTER};
	char thirdArg[] = { REGISTER };

	this->name = "Lldi";
	this->opCode = 0x0E;
	this->cycle = 50;
	this->has_index = true;
	this->index[0] = true;
	this->index[1] = true;
	this->index[2] = false;
	this->nbr_args = 3;
	this->types.push_back(std::vector<char>(firstArg, firstArg + sizeof(firstArg) / sizeof(char)));
	this->types.push_back(std::vector<char>(secondArg, secondArg + sizeof(secondArg) / sizeof(char)));
	this->types.push_back(std::vector<char>(thirdArg, thirdArg + sizeof(thirdArg) / sizeof(char)));
}

bool Lldi::load(Process *caller, std::vector<Param> &params, Arena &arena)
{
	std::vector<char>	data;

	this->values[0] = InstructionFactory::getParamValue(params[0], arena, caller, 2);
	this->values[1] = InstructionFactory::getParamValue(params[1], arena, caller);
	data = arena.get(caller->pc + (this->values[0] + this->values[1]), 1);
	this->values[2] = InstructionFactory::getDataValue(data);
	return true;
}

bool Lldi::execute(Process *caller, std::vector<Param> &params, Arena &arena)
{
	caller->registers[0] = this->values[2];
	arena.addEvent(caller->getParentId(), this->name, caller->registers[0],	0, true);
	if (caller->registers[0] == 0)
		caller->carry = true;
	else
		caller->carry = false;
	return true;
}


Lldi::~Lldi()
{
}
