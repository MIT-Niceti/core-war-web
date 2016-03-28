#pragma once
#include "Op.h"
class Ldi :
	public Op
{
public:
	virtual bool execute(Process *caller, std::vector<Param> &params, Arena &arena);
	Ldi();
	~Ldi();
};

