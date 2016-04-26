#pragma once

#include "Instruction.h"

class Arena;

class InstructionFactory
{
	static bool checkParam(Op *op, int param, char type);
	static char getParamFromByte(int param, char paramByte);
	static __int32 getParamValue(Arena &arena, int &index, char type);
	static bool getParams(Arena &arena, int &index, std::vector<Param> &params, Op *op);
	static char getParamType(Op *op, int param, char paramByte);

public:
	static __int32 getParamValue(Param &param, Arena &arena, Process *process, int size = 0);
	static __int32 getDataValue(std::vector<char> &data);
	static Instruction* getInstruction(Arena &arena, Process *caller);
	InstructionFactory();
	~InstructionFactory();
};

