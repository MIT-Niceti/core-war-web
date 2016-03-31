#include "stdafx.h"
#include "Lld.h"
#include "Process.h"
#include "Arena.h"

Lld::Lld()
{
	char firstArg[] = { DIRECT, INDIRECT };
	char secondArg[] = { REGISTER };

	this->name = "Lld";
	this->opCode = 0x0D;
	this->cycle = 10;
	this->nbr_args = 2;
	this->has_index = true;
	this->types.push_back(std::vector<char>(firstArg, firstArg + sizeof(firstArg) / sizeof(char)));
	this->types.push_back(std::vector<char>(secondArg, secondArg + sizeof(secondArg) / sizeof(char)));
}

bool Lld::load(Process *caller, std::vector<Param> &params, Arena &arena)
{
	std::vector<char>	data;

	if (params[0].type == INDIRECT)
	{
		data = arena.get(caller->pc + params[0].value, 1);
		this->values[0] = InstructionFactory::getDataValue(data);
	}
	else
		this->values[0] = params[0].value;
	return true;
}

bool Lld::execute(Process *caller, std::vector<Param> &params, Arena &arena)
{
	if (this->values[0] == 0)
		caller->carry = true;
	else
		caller->carry = false;
	caller->registers[params[1].value - 1] = this->values[0];
	arena.addEvent(caller->getParentId(), this->name, caller->registers[params[1].value - 1],
		params[1].value - 1, true);
	return true;
}

Lld::~Lld()
{
}
