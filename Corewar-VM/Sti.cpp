#include "stdafx.h"
#include "Sti.h"
#include "Process.h"
#include "Arena.h"

Sti::Sti()
{
	char firstArg[] = { REGISTER };
	char secondArg[] = { REGISTER, DIRECT, INDIRECT };
	char thirdArg[] = { REGISTER, DIRECT };

	this->name = "Sti";
	this->opCode = 0x0B;
	this->cycle = 25;
	this->nbr_args = 3;
	this->has_index = true;
	this->index[0] = false;
	this->index[1] = true;
	this->index[2] = true;
	this->index[3] = false;
	this->types.push_back(std::vector<char>(firstArg, firstArg + sizeof(firstArg) / sizeof(char)));
	this->types.push_back(std::vector<char>(secondArg, secondArg + sizeof(secondArg) / sizeof(char)));
	this->types.push_back(std::vector<char>(thirdArg, thirdArg + sizeof(thirdArg) / sizeof(char)));
}

bool Sti::execute(Process *caller, std::vector<Param> &params, Arena &arena)
{
	__int32				value1;
	__int32				value2;
	__int32				value3;
	std::vector<char>	data;

	value1 = InstructionFactory::getParamValue(params[0], arena, caller);
	value2 = InstructionFactory::getParamValue(params[1], arena, caller);
	value3 = InstructionFactory::getParamValue(params[2], arena, caller);
	data.push_back(value1);
	std::cout << "Using register " << params[0].value << std::endl;
	std::cout << "Data: " << value1 << " at " << value2 << " + " << value3 << std::endl;
	arena.load(caller->pc + ((value2 + value3) % IDX_MOD), data);
	return true;
}

Sti::~Sti()
{
}
