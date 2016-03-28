#pragma once

#include "Instruction.h"
#include "InstructionFactory.h"

class Champion;
class Arena;

class Process
{
private:
	Champion	*parent = NULL;
	int			lag;
	Instruction	*currentInstruction = NULL;

public:
	int			newPc;
	int			pc;
	char		registers[16];
	bool		carry = false;
	bool doCycle(Arena &arena);
	void fork(int pc);
	Process(Champion *parent, int pc, char registers[] = 0);
	~Process();
};

