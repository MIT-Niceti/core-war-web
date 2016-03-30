#pragma once
#include "Op.h"
class Ld :
	public Op
{
public:
	virtual bool execute(Process *caller, std::vector<Param> &params, Arena &arena);
	virtual bool load(Process *caller, std::vector<Param> &params, Arena &arena);
	Ld();
	~Ld();
};

