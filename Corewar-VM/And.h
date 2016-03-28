#pragma once
#include "Op.h"
class And :
	public Op
{
public:
	virtual bool execute(Process *caller, std::vector<Param> &params, Arena &arena);
	And();
	~And();
};

