#pragma once
#include "Op.h"
class Sti :
	public Op
{
public:
	bool execute(Process *caller, std::vector<Param> &params, Arena &arena);
	Sti();
	~Sti();
};

