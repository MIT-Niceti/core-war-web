#include "stdafx.h"
#include "Xor.h"
#include "Arena.h"
#include "Process.h"

Xor::Xor()
{
	char firstArg[] = { REGISTER, DIRECT, INDIRECT };
	char secondArg[] = { REGISTER, DIRECT, INDIRECT};
	char thirdArg[] = { REGISTER };

	this->name = "XOR";
	this->opCode = 0x08;
	this->cycle = 6;
	this->nbr_args = 3;
	this->types.push_back(std::vector<char>(firstArg, firstArg + sizeof(firstArg) / sizeof(char)));
	this->types.push_back(std::vector<char>(secondArg, secondArg + sizeof(secondArg) / sizeof(char)));
	this->types.push_back(std::vector<char>(thirdArg, thirdArg + sizeof(thirdArg) / sizeof(char)));
}

bool Xor::load(Process *caller, std::vector<Param> &params, Arena &arena)
{
	this->values[0] = InstructionFactory::getParamValue(params[0], arena, caller, 1);
	this->values[1] = InstructionFactory::getParamValue(params[1], arena, caller, 1);
	return true;
}

bool Xor::execute(Process *caller, std::vector<Param> &params, Arena &arena)
{
	std::vector<char> data;
	__int32	value1;
	__int32 value2;

	caller->registers[params[2].value - 1] = this->values[0] ^ this->values[1];
	if (caller->registers[params[2].value - 1] == 0)
		caller->carry = true;
	else
		caller->carry = false;
	return true;
}

Xor::~Xor()
{
}
