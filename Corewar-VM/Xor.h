#pragma once
#include "Op.h"
class Xor :
	public Op
{
public:
	virtual bool execute(Process *caller, std::vector<Param> &params, Arena &arena);
	Xor();
	~Xor();
};

