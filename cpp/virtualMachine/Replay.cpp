#include "stdafx.h"
#include "Replay.h"
#include <sstream>

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

std::string Replay::serialize(int winnerId)
{
	std::ostringstream json;

	json << "{ \"replay\": { \"winnerId\": " << winnerId << ", \"nbPlayers\": " << this->champions.size() << ", \"champions\": [ ";
	for (std::vector<ChampionRecap>::iterator it = champions.begin(); it != champions.end(); ++it)
	{
		json << '{' << "\"id\": " << it->id << ','
			<< "\"name\": \"" << it->name << "\","
			<< "\"init\": [";
		for (int i = 0; i < it->code->size(); i++)
		{
			json << (int)it->code->at(i);
			if (i + 1 < it->code->size())
				json << ',';
		}
		json << "], " << " \"entryPoint\": " << it->entryPoint << ','
			<< "\"registers\": " << it->id << " }";
		if ((it + 1) != champions.end())
			json << ',';
	}
	json << "],\"modifList\": [";
	for (std::vector<OpLog>::iterator ite = modifList.begin(); ite != modifList.end(); ++ite)
	{
		json << '{' << "\"cycle\": " << ite->cycle << ','
			<< "\"championId\": " << ite->championId << ','
			<< "\"op\": \"" << ite->op << "\","
			<< "\"wrote\": " << ite->wrote << ','
			<< "\"at\": " << ite->at;
		if (ite->reg)
			json << ",\"reg\": \"true\"";
		json << "}";
		if ((ite + 1) != modifList.end())
			json << ',';
	}
	json << "]}}";
	return json.str();
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
