#include "stdafx.h"
#include "InstructionFactory.h"
#include "Arena.h"

extern Op *OpTab[];

char InstructionFactory::getParamFromByte(int param, char paramByte)
{
	char	first = 7 - ((param * 2) - 2);
	char	second = first - 1;

	if (((paramByte >> first) & 0x1) && ((paramByte >> second) & 0x1))
		return INDIRECT;
	else if (((paramByte >> first) & 0x1) && !((paramByte >> second) & 0x1))
		return DIRECT;
	else if (!((paramByte >> first) & 0x1) && ((paramByte >> second) & 0x1))
		return REGISTER;
	std::cout << "Bad param type" << std::endl;
	return 0;
}

bool InstructionFactory::checkParam(Op *op, int param, char type)
{
	int	i = 0;

	for (std::vector<std::vector<char>>::iterator it = op->types.begin(); it != op->types.end(); ++it)
	{
		if (i == param - 1)
		{
			for (std::vector<char>::iterator iterator = (*it).begin(); iterator != (*it).end(); ++iterator)
				if (*iterator == type)
					return true;
		}
		++i;
	}
	return false;
}

char InstructionFactory::getParamType(Op *op, int param, char paramByte)
{
	int	i = 0;
	char type = 0;

	if (paramByte == 0)
	{
		for (std::vector<std::vector<char>>::iterator it = op->types.begin(); it != op->types.end(); ++it)
			if (i == param - 1)
				type = (*it)[0];
	}
	else
		type = getParamFromByte(param, paramByte);
	if (checkParam(op, param, type))
		return type;
	std::cout << "Not allowed param" << std::endl;
	return 0;
}

__int32 bitsToInt(__int32 &result, const char* bits, bool little_endian = true)
{
	result = 0;
	if (little_endian)
	for (int n = sizeof(result); n >= 0; n--)
		result = (result << 8) + bits[n];
	else
	for (unsigned n = 0; n < sizeof(result); n++)
		result = (result << 8) + bits[n];
	if (result < -255)
		result += 256;
	return result;
}

__int32 InstructionFactory::getDataValue(std::vector<char> &data)
{
	std::vector<char>   fixedData;
	__int32				ret;

	if (data.size() < 4)
	{
		for (int i = 0; i < 4 - data.size(); i++)
			fixedData.push_back(0x00);
		fixedData.insert(fixedData.end(), data.begin(), data.end());
		return bitsToInt(ret, fixedData.data(), false);
	}
	else
		return bitsToInt(ret, data.data(), false);
}

__int32	InstructionFactory::getParamValue(Arena &arena, int &index, char type)
{
	std::vector<char>	data;
	std::vector<char>   fixedData;
	__int32				ret;

	if (type == REGISTER)
		data = arena.get(index++, 1);
	else if (type == DIRECT)
	{
		data = arena.get(index, 4);
		index += 4;
	}
	else if (type == INDIRECT)
	{
		data = arena.get(index, 2);
		index += 2;
	}
	if (index >= (6 * 1024))
		index = index - (6 * 1024);
	return getDataValue(data);
}

bool InstructionFactory::getParams(Arena &arena, int &index, std::vector<Param> &params, Op *op)
{
	char	paramByte = 0;
	Param	param;
	char	type = 0;
	int		i = 0;

	if (op->paramByte)
	{
		paramByte = arena.get(index++, 1)[0];
		if (paramByte == 0x00)
			return false;
	}
	while (i != op->nbr_args)
	{
		if ((param.type = getParamType(op, i + 1, paramByte)) == 0)
			return false;
		if (op->has_index && op->index[i])
			param.value = getParamValue(arena, index, INDIRECT);
		else
			param.value = getParamValue(arena, index, param.type);
		if (param.type == REGISTER && (param.value < 0 || param.value > 16))
			return false;
		params.push_back(param);
		++i;
	}
	return true;
}

__int32 InstructionFactory::getParamValue(Param &param, Arena &arena, Process *caller, int size)
{
	__int32	ret = 0;
	std::vector<char> data;

	if (param.type == REGISTER)
		ret = caller->registers[param.value - 1];
	else if (param.type == DIRECT)
		ret = param.value;
	else if (param.type == INDIRECT && size > 0)
	{
		data = arena.get(caller->pc + (param.value % IDX_MOD), size);
		ret = InstructionFactory::getDataValue(data);
	}
	return ret;
}

Instruction	*InstructionFactory::getInstruction(Arena &arena, Process *caller)
{
	int					i = 0;
	std::vector<char>	data;
	std::vector<Param>	params;
	Op					*op;

	data = arena.get(caller->newPc, 1);
	if (caller->newPc == (6 * 1024) - 1)
		caller->newPc = 0;
	else
		caller->newPc += 1;
	if (data[0] <= 0x00 || data[0] - 1 >= 16)
	{
		std::cout << "Bad opcode: " << (int)data[0] << std::endl;
		if (data[0] == 0x00)
			caller->newPc = -1;
		return NULL;
	}
	op = OpTab[data[0] - 1];
	if (op->opCode != data[0])
		return NULL;
	if (!getParams(arena, caller->newPc, params, op))
	{
		std::cout << "Bad params" << std::endl;
		return NULL;
	}
	std::cout << "Read command: " << op->name << "With args: " << std::endl;;
	for (i = 0; i < op->nbr_args; i++)
		std::cout << "Type: " << params[i].type << " Value: " << params[i].value << std::endl;
	return new Instruction(op, params, caller);
}

InstructionFactory::InstructionFactory()
{
}


InstructionFactory::~InstructionFactory()
{
}
