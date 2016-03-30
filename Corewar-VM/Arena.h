#pragma once

#define CYCLE_TO_DIE 1536
#define CYCLE_DELTA 5
#define NBR_LIVE 40
#define IDX_MOD 512

#include "Champion.h"
#include "Operations.h"
#include "v8.h"

int startMachine(std::vector<std::string> &champions);
class Arena
{
private:
	char				arena[6 * 1024];
	std::list<Champion> champions;
	int					cycle_total = 0;
	int					check_count = 0;
	int					cycle_to_die = 1536;
	bool				ready = false;

	bool checkLive();
	bool isLittleEndian();
	bool loadChampions(std::vector<std::string> &champions);
public:
	void setLive(int id);
	bool load(int offset, std::vector<char> &data);
	bool load(int offset, std::string &data);
	std::vector<char> get(int offset, int size);
	bool setupArena(std::vector<std::string> &champions);
	bool start(void);
	void dumpArena(void);
	Arena();
	~Arena();
};
