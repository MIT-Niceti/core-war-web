#include "stdafx.h"
#include "Process.h"

#include "Champion.h"
#include "Arena.h"

void Process::fork(int pc)
{
//	this->parent->
}

bool Process::doCycle(Arena &arena)
{
	if (this->currentInstruction == NULL)
	{
		this->currentInstruction = InstructionFactory::getInstruction(arena, this);
		if (this->newPc == -1)
			return false;
		if (!this->currentInstruction)
			return true;
		this->lag = this->currentInstruction->op->cycle;
	}
	this->lag -= 1;
	if (this->lag == 0)
	{
		std::cout << "Executing " << this->currentInstruction->op->name << std::endl;
		if (!this->currentInstruction->exec(arena))
			return false;
		delete this->currentInstruction;
		this->currentInstruction = NULL;
		this->pc = newPc;
	}
	else
		std::cout << "Waiting, left: " << this->lag << std::endl;
	return true;
}

Process::Process(Champion *parent, int pc, char registers[])
{
	this->pc = pc;
	this->newPc = pc;
	this->parent = parent;
	if (registers != 0)
		for (int i = 0; i < 16; i++)
			this->registers[i] = registers[i];
	else
		for (int i = 0; i < 16; i++)
			this->registers[i] = 0;
	this->registers[0] = parent->id;
}


Process::~Process()
{
}
