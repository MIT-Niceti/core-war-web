#include "stdafx.h"
#include "Champion.h"
#include "Arena.h"

void Champion::fork(Process &process, int pc, Arena &arena)
{
	if (this->processes.size() > 1000) {
		return;
	}
	if (pc >= 6 * 1024)
	{
		while (pc >= (6 * 1024))
			pc -= (6 * 1024);
	}
	else if (pc < 0)
	{
		while (pc < 0)
			pc += (6 * 1024);
	}

	arena.load(pc, *(this->code));
	this->processes.push_back(Process(this, pc, &process));
}

std::string Champion::getName()
{
	return std::string(this->header.name);
}

s_header Champion::getHeader()
{
	return (this->header);
}

void Champion::addProcess(int pc)
{
	this->processes.push_back(Process(this, pc));
}

bool Champion::doCycle(Arena &arena)
{
	for (std::list<Process>::iterator it = this->processes.begin(); it != this->processes.end(); ++it)
	{
		if (!it->doCycle(arena))
			continue;
	}
	return true;
}

Champion::Champion(s_header header, std::vector<char> *code, int id, int pc)
{
	this->header = header;
	this->code = code;
	this->id = id;
}


Champion::~Champion()
{
}
