#include "stdafx.h"
#include "Add.h"
#include "Process.h"

Add::Add()
{
	char firstArg[] = { REGISTER };
	char secondArg[] = { REGISTER };
	char thirdArg[] = { REGISTER };

	this->name = "Add";
	this->opCode = 0x04;
	this->cycle = 10;
	this->nbr_args = 3;
	this->paramByte = false;
	this->types.push_back(std::vector<char>(firstArg, firstArg + sizeof(firstArg) / sizeof(char)));
	this->types.push_back(std::vector<char>(secondArg, secondArg + sizeof(secondArg) / sizeof(char)));
	this->types.push_back(std::vector<char>(thirdArg, thirdArg + sizeof(thirdArg) / sizeof(char)));
}

bool Add::load(Process *caller, std::vector<Param> &params, Arena &arena)
{
	return true;
}

bool Add::execute(Process *caller, std::vector<Param> &params, Arena &arena)
{
	caller->registers[params[2].value - 1] = caller->registers[params[0].value - 1]
												+ caller->registers[params[1].value - 1];
	if (caller->registers[params[2].value - 1] == 0)
		caller->carry = true;
	else
		caller->carry = false;
	return true;
}


Add::~Add()
{
}
