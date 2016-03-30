#include "stdafx.h"
#include "Or.h"
#include "Process.h"
#include "Arena.h"

Or::Or()
{
	char firstArg[] = { REGISTER, INDIRECT, DIRECT };
	char secondArg[] = { REGISTER, INDIRECT, DIRECT };
	char thirdArg[] = { REGISTER };

	this->name = "Or";
	this->opCode = 0x07;
	this->cycle = 6;
	this->nbr_args = 3;
	this->types.push_back(std::vector<char>(firstArg, firstArg + sizeof(firstArg) / sizeof(char)));
	this->types.push_back(std::vector<char>(secondArg, secondArg + sizeof(secondArg) / sizeof(char)));
	this->types.push_back(std::vector<char>(thirdArg, thirdArg + sizeof(thirdArg) / sizeof(char)));
}

bool Or::load(Process *caller, std::vector<Param> &params, Arena &arena)
{
	this->values[0] = InstructionFactory::getParamValue(params[0], arena, caller, 1);
	this->values[1] = InstructionFactory::getParamValue(params[1], arena, caller, 1);
	return true;
}

bool Or::execute(Process *caller, std::vector<Param> &params, Arena &arena)
{
	caller->registers[params[2].value - 1] = this->values[0] | this->values[1];
	if (caller->registers[params[2].value - 1] == 0)
		caller->carry = true;
	else
		caller->carry = false;
	return true;
}


Or::~Or()
{
}
