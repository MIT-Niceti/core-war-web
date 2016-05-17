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
	for (std::list<std::vector<DataCell>>::iterator ite = this->snapshot.begin(); ite != this->snapshot.end(); ++ite)
	{
		std::cout << "SNAPSHOT: " << std::endl;
		for (std::vector<DataCell>::iterator snap = ite->begin(); snap != ite->end(); snap++)
		{
			std::cout << "Champion id: " << snap->championId << " at position: " << snap->coord << std::endl;
		}
		std::cout << "------" << std::endl;
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
	json << "],\"modifList\": ";
	json << "[";
	for (std::list<std::vector<DataCell>>::iterator ite = this->snapshot.begin(); ite != this->snapshot.end(); ++ite)
	{
		json << "[";
		for (std::vector<DataCell>::iterator snap = ite->begin(); snap != ite->end(); snap++)
		{
			json << "{";
			json << " \"championId\": " << snap->championId << " ,";
			json << " \"position\":" << snap->coord;
			json << "}";
			if ((snap + 1) != ite->end())
				json << ',';
		}
		json << "]";
		if (++ite != this->snapshot.end())
			json << ',';
		--ite;
	}
	json << "]";
	json << "}}";
	return json.str();
}

bool Replay::saveSnapshot()
{
	int	i = 0;
	DataCell elem;
	std::vector<DataCell> vector = std::vector<DataCell>();

	while (i != 6 * 1024)
	{
		if (this->modifTab[i].changed)
		{
			elem.championId = this->modifTab[i].championId;
			elem.coord = i;
			vector.push_back(elem);
			this->modifTab[i].changed = false;
		}
		++i;
	}
	if (vector.size() >= 1)
		this->snapshot.push_back(vector);
	return true;
}

bool Replay::addEvent(int championId, const std::string &op,
						int wrote, int at, bool reg)
{
	int		i = 0;

//	log.at = at;
	if (at != -1 && reg == false) {
		if (op == "Fork" || op == "Lfork")
		{
			while (i != wrote) {
				if (at == 1024 * 6)
					at = 0;
				if (this->modifTab[at].championId != championId) {
					this->modifTab[at].championId = championId;
					this->modifTab[at].changed = true;
				}
				++i;
				++at;
			}
		}
		else
		{
			if (this->modifTab[at].championId != championId) {
				this->modifTab[at].championId = championId;
				this->modifTab[at].changed = true;
			}
		}
	}
/*	log.wrote = wrote;
	log.op = op;
	log.reg = reg;
	log.championId = championId;
	log.cycle = cycle;
	log.championName = championName;
	this->modifList.push_back(log);*/
	return true;
}

bool Replay::setReplay(std::vector<ChampionRecap> &champions)
{
	this->champions = champions;
	return true;
}

Replay::Replay()
{
	int	i = 0;

	while (i != 6 * 1024) {
		this->modifTab[i].championId = -1;
		this->modifTab[i].changed = false;
		++i;
	}
}


Replay::~Replay()
{
}
