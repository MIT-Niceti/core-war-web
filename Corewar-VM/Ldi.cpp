#include "stdafx.h"
#include "Ldi.h"
#include "Process.h"
#include "Arena.h"

Ldi::Ldi()
{
	char firstArg[] = { REGISTER, DIRECT, INDIRECT };
	char secondArg[] = { REGISTER, DIRECT };
	char thirdArg[] = { REGISTER };

	this->name = "Ldi";
	this->opCode = 0x0A;
	this->cycle = 25;
	this->has_index = true;
	this->index[0] = true;
	this->index[1] = true;
	this->index[2] = false;
	this->nbr_args = 3;
	this->types.push_back(std::vector<char>(firstArg, firstArg + sizeof(firstArg) / sizeof(char)));
	this->types.push_back(std::vector<char>(secondArg, secondArg + sizeof(secondArg) / sizeof(char)));
	this->types.push_back(std::vector<char>(thirdArg, thirdArg + sizeof(thirdArg) / sizeof(char)));
}

bool Ldi::execute(Process *caller, std::vector<Param> &params, Arena &arena)
{
	__int32				value1;
	__int32				value2;
	std::vector<char>	data;

	value1 = InstructionFactory::getParamValue(params[0], arena, caller, 2);
	value2 = InstructionFactory::getParamValue(params[1], arena, caller);
	data = arena.get(caller->pc + ((value1 + value2) % IDX_MOD), 1);
	caller->registers[0] = InstructionFactory::getDataValue(data);
	if (caller->registers[0] == 0)
		caller->carry = true;
	else
		caller->carry = false;
	return true;
}

Ldi::~Ldi()
{
}
