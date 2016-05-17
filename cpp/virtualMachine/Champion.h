#pragma once

#include "Process.h"

class Arena;

struct s_header
{
	uint32_t		magic;
	char	name[128];
	unsigned int		prog_size;
	char	comment[2048];
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
	s_header getHeader();
	void fork(Process &process, int pc, Arena &arena);
	void addProcess(int pc);
	bool doCycle(Arena &arena);
	std::string getName();
	Champion(s_header header, std::vector<char> *code, int id, int pc);
	~Champion();
};
