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

bool Lldi::execute(Process *caller, std::vector<Param> &params, Arena &arena)
{
	__int32				value1;
	__int32				value2;
	std::vector<char>	data;

	value1 = InstructionFactory::getParamValue(params[0], arena, caller, 2);
	value2 = InstructionFactory::getParamValue(params[1], arena, caller);
	data = arena.get(caller->pc + (value1 + value2), 1);
	caller->registers[0] = InstructionFactory::getDataValue(data);
	if (caller->registers[0] == 0)
		caller->carry = true;
	else
		caller->carry = false;
	return true;
}


Lldi::~Lldi()
{
}
