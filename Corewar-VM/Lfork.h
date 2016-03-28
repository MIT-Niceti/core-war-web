#pragma once
#include "Op.h"
class Lfork :
	public Op
{
public:
	virtual bool execute(Process *caller, std::vector<Param> &params, Arena &arena);
	Lfork();
	~Lfork();
};

