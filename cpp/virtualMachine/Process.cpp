#include "stdafx.h"
#include "Process.h"

#include "Champion.h"
#include "Arena.h"

void Process::fork(int pc, Arena &arena)
{
	this->parent->fork(*this, pc, arena);
}

int Process::getParentId(void)
{
	if (this->parent != NULL)
		return this->parent->id;
	return 0;
}

bool Process::doCycle(Arena &arena)
{
	if (this->currentInstruction == NULL)
	{
		this->currentInstruction = InstructionFactory::getInstruction(arena, this);
		if (!this->currentInstruction)
		{
			this->pc += 1;
			this->newPc = this->pc;
			return true;
		}
		this->currentInstruction->load(arena);
		this->lag = this->currentInstruction->op->cycle;
	}
	this->lag -= 1;
	if (this->lag == 0)
	{
		if (!this->currentInstruction->exec(arena))
			return false;
		delete this->currentInstruction;
		this->currentInstruction = NULL;
		this->pc = newPc;
	}
	return true;
}

Process::Process(Champion *parent, int pc, Process *process)
{
	this->pc = pc;
	this->newPc = pc;
	this->carry = 0;
	this->parent = parent;
	if (process != NULL)
	{
		for (int i = 0; i < 16; i++)
			this->registers[i] = process->registers[i];
		this->carry = process->carry;
	}
	else
		for (int i = 0; i < 16; i++)
			this->registers[i] = 0;
	this->registers[0] = parent->id;
}


Process::~Process()
{
}
