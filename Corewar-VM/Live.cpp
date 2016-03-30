#include "stdafx.h"
#include "Live.h"
#include "Arena.h"

Live::Live()
{
	char firstArg[] = { DIRECT };

	this->name = "Live";
	this->opCode = 0x01;
	this->cycle = 10;
	this->nbr_args = 1;
	this->paramByte = false;
	this->types.push_back(std::vector<char>(firstArg, firstArg + sizeof(firstArg) / sizeof(char)));
}

bool Live::load(Process *caller, std::vector<Param> &params, Arena &arena)
{
	return true;
}

bool Live::execute(Process *caller, std::vector<Param> &params, Arena &arena)
{
	arena.setLive(params[0].value);
	return true;
}

Live::~Live()
{
}
