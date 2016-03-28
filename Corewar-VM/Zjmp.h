#pragma once

#include "Op.h"

class Zjmp :
	public Op
{
public:
	Zjmp();
	~Zjmp();
	virtual bool execute(Process *caller, std::vector<Param> &params, Arena &arena);
};

