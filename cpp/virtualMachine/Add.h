#pragma once
#include "Op.h"
class Add :
	public Op
{
public:
	Add();
	~Add();
	virtual bool load(Process *caller, std::vector<Param> &params, Arena &arena);
	virtual bool execute(Process *caller, std::vector<Param> &params, Arena &arena);
};

