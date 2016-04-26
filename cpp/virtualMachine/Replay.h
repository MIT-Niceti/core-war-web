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

class Replay
{
public: 
	int nb_players = 0;
	std::vector<ChampionRecap> champions;
	std::vector<OpLog> modifList;

public:
	bool setReplay(std::vector<ChampionRecap> &champions);
	bool addEvent(int cycle, int championId, std::string &championName, std::string &op,
					int wrote, int at, bool reg = false);
	void dumpReplay(void);
	Replay();
	~Replay();
};

