#include "stdafx.h"
#include "Sub.h"
#include "Process.h"


Sub::Sub()
{
	char firstArg[] = { REGISTER };
	char secondArg[] = { REGISTER };
	char thirdArg[] = { REGISTER };

	this->name = "Sub";
	this->opCode = 0x05;
	this->cycle = 10;
	this->nbr_args = 3;
	this->paramByte = false;
	this->types.push_back(std::vector<char>(firstArg, firstArg + sizeof(firstArg) / sizeof(char)));
	this->types.push_back(std::vector<char>(secondArg, secondArg + sizeof(secondArg) / sizeof(char)));
	this->types.push_back(std::vector<char>(thirdArg, thirdArg + sizeof(thirdArg) / sizeof(char)));
}

bool Sub::execute(Process *caller, std::vector<Param> &params, Arena &arena)
{
	caller->registers[params[2].value - 1] = caller->registers[params[0].value - 1]
		- caller->registers[params[1].value - 1];
	if (caller->registers[params[2].value - 1] == 0)
		caller->carry = true;
	else
		caller->carry = false;
	return true;
}

Sub::~Sub()
{
}
