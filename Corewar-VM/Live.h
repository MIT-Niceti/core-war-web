#pragma once
#include "Op.h"
class Live :
	public Op
{
public:
	virtual bool execute(Process *caller, std::vector<Param> &params, Arena &arena);
	Live();
	~Live();
};

