#pragma once

#include "Param.h"
#include "stdafx.h"


class Process;
class Arena;

class Op
{
#define REGISTER	1
#define DIRECT		2
#define INDIRECT	3

public:
	std::string			name;
	char				opCode;
	bool				paramByte = true;
	char				nbr_args;
	bool				has_index = false;
	bool				index[4];
	std::vector<std::vector<char>>	types;
	int					values[3];
	int					cycle;

public:
	virtual bool load(Process *caller, std::vector<Param> &params, Arena &arena) = 0;
	virtual bool execute(Process *caller, std::vector<Param> &params, Arena &arena) = 0;
	virtual ~Op(){};
};