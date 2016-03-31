#include "stdafx.h"
#include "Ld.h"
#include "Arena.h"
//#include "InstructionFactory.h"
#include "Process.h"


Ld::Ld()
{
	char firstArg[] = { DIRECT, INDIRECT };
	char secondArg[] = { REGISTER };

	this->name = "Ld";
	this->opCode = 0x02;
	this->cycle = 5;
	this->nbr_args = 2;
	this->types.push_back(std::vector<char>(firstArg, firstArg + sizeof(firstArg) / sizeof(char)));
	this->types.push_back(std::vector<char>(secondArg, secondArg + sizeof(secondArg) / sizeof(char)));
}

bool Ld::load(Process *caller, std::vector<Param> &params, Arena &arena)
{
	std::vector<char>	data;

	if (params[0].type == INDIRECT)
	{
		data = arena.get(caller->pc + (params[0].value % IDX_MOD), 1);
		caller->values[0] = InstructionFactory::getDataValue(data);
	}
	else
		caller->values[0] = params[0].value;
	return true;
}

bool Ld::execute(Process *caller, std::vector<Param> &params, Arena &arena)
{
	caller->registers[params[1].value - 1] = caller->values[0];
	if (caller->values[0] == 0)
		caller->carry = true;
	else
		caller->carry = false;

	arena.addEvent(caller->getParentId(), this->name, caller->registers[params[1].value - 1],
		params[1].value - 1, true);
	return true;
}


Ld::~Ld()
{
}
