#pragma once
#include "Op.h"
class Lldi :
	public Op
{
public:
	virtual bool execute(Process *caller, std::vector<Param> &params, Arena &arena);
	Lldi();
	~Lldi();
};

