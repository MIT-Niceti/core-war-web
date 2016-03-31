#include "stdafx.h"
#include "Aff.h"
#include "Process.h"
#include "Arena.h"

Aff::Aff()
{
	char firstArg[] = { REGISTER };

	this->name = "Aff";
	this->opCode = 0x10;
	this->cycle = 2;
	this->paramByte = false;
	this->nbr_args = 1;
	this->types.push_back(std::vector<char>(firstArg, firstArg + sizeof(firstArg) / sizeof(char)));
}

bool Aff::load(Process *caller, std::vector<Param> &params, Arena &arena)
{
	return true;
}

bool Aff::execute(Process *caller, std::vector<Param> &params, Arena &arena)
{
	char	value1;

	value1 = InstructionFactory::getParamValue(params[0], arena, caller);
	arena.addEvent(caller->getParentId(), this->name, value1, -1);
	std::cout << value1;
	return true;
}


Aff::~Aff()
{
}
