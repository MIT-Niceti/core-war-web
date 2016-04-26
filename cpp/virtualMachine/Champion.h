#pragma once

#include "Process.h"

class Arena;

struct s_header
{
	int		magic;
	char	name[128 + 1];
	int		prog_size;
	char	comment[2048 + 1];
};

class Champion
{
private:
	s_header			header;
	std::list<Process>	processes;
	std::vector<char>	*code = NULL;

public:
	int					id;
	bool				live;
	void fork(Process &process, int pc);
	void addProcess(int pc);
	bool doCycle(Arena &arena);
	std::string getName();
	Champion(s_header header, std::vector<char> *code, int id, int pc);
	~Champion();
};

