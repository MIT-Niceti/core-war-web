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

bool And::execute(Process *caller, std::vector<Param> &params, Arena &arena)
{
	std::vector<char> data;
	__int32	value1;
	__int32 value2;

	value1 = InstructionFactory::getParamValue(params[0], arena, caller, 1);
	value2 = InstructionFactory::getParamValue(params[1], arena, caller, 1);
	caller->registers[params[2].value - 1] = value1 & value2;
	if (caller->registers[params[2].value - 1] == 0)
		caller->carry = true;
	else
		caller->carry = false;
	return true;
}


And::~And()
{
}
