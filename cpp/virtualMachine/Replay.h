#pragma once

struct ChampionRecap
{
public:
	int entryPoint;
	int size;
	int	id;
	std::string name;
	std::vector<char>	*code;
};

struct OpLog
{
	int cycle;
	int championId;
	std::string championName;
	std::string op;
	int wrote;
	int at;
	bool reg;
};

struct MemoryCell
{
	int championId;
	bool changed;
};

struct DataCell
{
	int championId;
	int coord;
};

class Replay
{
public:
	int nb_players = 0;
	MemoryCell modifTab[6 * 1024];
	std::list<std::vector<DataCell>> snapshot;
	std::vector<ChampionRecap> champions;
	std::vector<OpLog> modifList;

public:
	bool saveSnapshot();
	bool setReplay(std::vector<ChampionRecap> &champions);
	bool addEvent(int championId, std::string &op,
					int wrote, int at, bool reg = false);
	void dumpReplay(void);
	std::string serialize(int winnerId);
	Replay();
	~Replay();
};
