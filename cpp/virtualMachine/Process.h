#pragma once

#include "Instruction.h"
#include "InstructionFactory.h"

class Champion;
class Arena;

class Process
{
private:
	int			lag;
	Instruction	*currentInstruction = NULL;

public:
	Champion	*parent = NULL;
	int			values[3];
	int			newPc;
	int			pc;
	char		registers[16];
	bool		carry = false;
	bool doCycle(Arena &arena);
	void fork(int pc, Arena &arena);
	int getParentId(void);
	Process(Champion *parent, int pc, Process *process = NULL);
	~Process();
};
