#pragma once
#include "Op.h"
class Sti :
	public Op
{
public:
	bool load(Process *caller, std::vector<Param> &params, Arena &arena);
	bool execute(Process *caller, std::vector<Param> &params, Arena &arena);
	Sti();
	~Sti();
};

