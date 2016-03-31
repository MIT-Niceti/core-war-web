#include "stdafx.h"
#include "And.h"
#include "Process.h"
#include "Arena.h"


And::And()
{
	char firstArg[] = { REGISTER, DIRECT, INDIRECT};
	char secondArg[] = { REGISTER, DIRECT, INDIRECT };
	char thirdArg[] = { REGISTER };

	this->name = "And";
	this->opCode = 0x06;
	this->cycle = 6;
	this->nbr_args = 3;
	this->types.push_back(std::vector<char>(firstArg, firstArg + sizeof(firstArg) / sizeof(char)));
	this->types.push_back(std::vector<char>(secondArg, secondArg + sizeof(secondArg) / sizeof(char)));
	this->types.push_back(std::vector<char>(thirdArg, thirdArg + sizeof(thirdArg) / sizeof(char)));

}

bool And::load(Process *caller, std::vector<Param> &params, Arena &arena)
{
	this->values[0] = InstructionFactory::getParamValue(params[0], arena, caller, 1);
	this->values[1] = InstructionFactory::getParamValue(params[1], arena, caller, 1);
	this->values[2] = params[2].value - 1;
	return true;
}

bool And::execute(Process *caller, std::vector<Param> &params, Arena &arena)
{
	std::vector<char> data;

	caller->registers[this->values[2]] = this->values[0] & this->values[1];
	arena.addEvent(caller->getParentId(), this->name, caller->registers[this->values[2]],
		this->values[2], true);
	if (caller->registers[params[2].value - 1] == 0)
		caller->carry = true;
	else
		caller->carry = false;
	return true;
}


And::~And()
{
}
