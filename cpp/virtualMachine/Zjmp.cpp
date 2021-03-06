#include "stdafx.h"
#include "Zjmp.h"
#include "Process.h"
#include "Arena.h"


bool Zjmp::load(Process *caller, std::vector<Param> &params, Arena &arena)
{
	return true;
}

bool Zjmp::execute(Process *caller, std::vector<Param> &params, Arena &arena)
{
	if (caller->carry)
	{
		caller->pc = caller->pc + (params[0].value % IDX_MOD);
		if (caller->pc >= 6 * 1024)
		{
			while (caller->pc >= (6 * 1024))
				caller->pc -= (6 * 1024);
		}
		else if (caller->pc < 0)
		{
			while (caller->pc < 0)
				caller->pc += (6 * 1024);
		}
		arena.addEvent(caller->getParentId(), this->name, -1, caller->pc);
		caller->newPc = caller->pc;
//		std::cout << "Jumping at " << caller->pc << std::endl;
	}
	else
		std::cout << "Carry not set for champion id: " << caller->parent->id << std::endl;
	return true;
}

Zjmp::Zjmp()
{
	char firstArg[] = { DIRECT };

	this->name = "Zjmp";
	this->opCode = 0x09;
	this->cycle = 20;
	this->paramByte = false;
	this->has_index = true;
	this->index[0] = true;
	this->index[1] = false;
	this->index[2] = false;
	this->nbr_args = 1;
	this->types.push_back(std::vector<char>(firstArg, firstArg + sizeof(firstArg) / sizeof(char)));
}

Zjmp::~Zjmp()
{
}
