#pragma once
#include "Op.h"
class Aff :
	public Op
{
public:
	Aff();
	~Aff();
	virtual bool load(Process *caller, std::vector<Param> &params, Arena &arena);
	virtual bool execute(Process *caller, std::vector<Param> &params, Arena &arena);
};

