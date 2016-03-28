#include "stdafx.h"
#include "Champion.h"
#include "Arena.h"

void Champion::fork(Process &process, int pc)
{
	this->processes.push_back(Process(this, pc, process.registers));
}

bool Champion::doCycle(Arena &arena)
{
	for (std::list<Process>::iterator it = this->processes.begin(); it != this->processes.end(); ++it)
	{
		if (!it->doCycle(arena))
			return false;
	}
	return true;
}

Champion::Champion(s_header header, std::vector<char> *code, int id, int pc)
{
	this->header = header;
	this->id = id;
	this->processes.push_back(Process(this, pc));
}


Champion::~Champion()
{
}
