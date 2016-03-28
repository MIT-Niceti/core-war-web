#pragma once
#include "Op.h"
class Lld :
	public Op
{
public:
	virtual bool execute(Process *caller, std::vector<Param> &params, Arena &arena);
	Lld();
	~Lld();
};

