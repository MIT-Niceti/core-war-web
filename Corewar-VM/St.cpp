#include "stdafx.h"
#include "St.h"
#include "Process.h"
#include "Arena.h"

St::St()
{
	char firstArg[] = { REGISTER };
	char secondArg[] = { REGISTER, INDIRECT };

	this->name = "St";
	this->opCode = 0x03;
	this->cycle = 10;
	this->nbr_args = 2;
	this->types.push_back(std::vector<char>(firstArg, firstArg + sizeof(firstArg) / sizeof(char)));
	this->types.push_back(std::vector<char>(secondArg, secondArg + sizeof(secondArg) / sizeof(char)));
}

bool St::load(Process *caller, std::vector<Param> &params, Arena &arena)
{
	return true;
}

bool St::execute(Process *caller, std::vector<Param> &params, Arena &arena)
{
	char value;
	std::vector<char> data;

	value = caller->registers[params[0].value - 1];
	if (params[1].type == INDIRECT)
	{
		data.push_back(value);
		arena.load(caller->pc + (params[1].value % IDX_MOD), data);
		arena.addEvent(caller->getParentId(), this->name, value, caller->pc + (params[1].value % IDX_MOD));
	}
	else if (params[1].type == REGISTER)
	{
		caller->registers[params[1].value - 1] = value;
		arena.addEvent(caller->getParentId(), this->name, caller->registers[params[1].value - 1],
			params[1].value - 1, true);
	}
	return true;
}

St::~St()
{
}
