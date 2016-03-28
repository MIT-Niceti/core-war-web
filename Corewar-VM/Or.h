#pragma once
#include "Op.h"
class Or :
	public Op
{
public:
	virtual bool execute(Process *caller, std::vector<Param> &params, Arena &arena);
	Or();
	~Or();
};

