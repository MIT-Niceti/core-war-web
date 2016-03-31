#include "stdafx.h"
#include "Replay.h"

void Replay::dumpReplay(void)
{
	std::cout << "I- Champions: " << std::endl;
	for (std::vector<ChampionRecap>::iterator it = champions.begin(); it != champions.end(); ++it)
	{
		std::cout << "	- Name: " << it->name << " Id number: " << it->id << " size: " << it->size
			<< " entry point: " << it->entryPoint << std::endl;
	}
	std::cout << "\nII- Modif list:" << std::endl;
	for (std::vector<OpLog>::iterator ite = modifList.begin(); ite != modifList.end(); ++ite)
	{
		std::cout << "	- Cycle" << ite->cycle << " Champion id: " << ite->championId 
			<< " Op: " << ite->op << " Value: " << ite->wrote	<< " At ";
		if (ite->reg)
			std::cout << "register: ";
		else
			std::cout << "adress: ";
		std::cout << ite->at << std::endl;
	}
}

bool Replay::addEvent(int cycle, int championId, std::string &championName, std::string &op,
						int wrote, int at, bool reg)
{
	OpLog log;

	log.at = at;
	log.wrote = wrote;
	log.op = op;
	log.reg = reg;
	log.championId = championId;
	log.cycle = cycle;
	log.championName = championName;
	this->modifList.push_back(log);
	return true;
}

bool Replay::setReplay(std::vector<ChampionRecap> &champions)
{
	this->champions = champions;
	return true;
}

Replay::Replay()
{
}


Replay::~Replay()
{
}
