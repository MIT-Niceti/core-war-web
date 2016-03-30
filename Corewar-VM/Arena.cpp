#include "stdafx.h"
#include "Arena.h"
#include <intrin.h>

Op *OpTab[16] =
{
	new Live(),
	new Ld(),
	new St(),
	new Add(),
	new Sub(),
	new And(),
	new Or(),
	new Xor(),
	new Zjmp(),
	new Ldi(),
	new Sti(),
	new Fork(),
	new Lld(),
	new Lldi(),
	new Lfork(),
	new Aff()
};

bool	Arena::isLittleEndian()
{
	short int number = 0x1;
	char *numPtr = (char*)&number;
	return (numPtr[0] == 1);
}

bool	Arena::loadChampions(std::vector<std::string> &champions)
{
	int					delta;
	std::ifstream		file;
	s_header			header;
	int					id = 1;
	int					pc = 0;
	std::vector<char>	*code;

	delta = (6 * 1024) / champions.size();
	for (std::vector<std::string>::iterator it = champions.begin(); it != champions.end(); ++it)
	{
		file.open(*it, std::ifstream::binary | std::ifstream::in);
		file.read((char *)&header, sizeof(header));
		header.name[128] = '\0';
		header.comment[2048] = '\0';
		if (isLittleEndian())
		{
			header.magic = _byteswap_ulong(header.magic);
			header.prog_size = _byteswap_ulong(header.prog_size);
		}
		code = new std::vector<char>(header.prog_size);
		file.read((char *)code->data(), header.prog_size);
		if (header.magic != 0xB16B00B5)
		{
			std::cout << "Bad magic number";
			file.close();
			continue;
		}
		this->champions.push_back(Champion(header, code, id++, pc));
		load(pc, *code);
		file.close();
		pc += delta;
	}
	return true;
}

void	Arena::setLive(int id)
{
	for (std::list<Champion>::iterator it = champions.begin(); it != champions.end(); ++it)
	{
		if (it->id == id)
		{
			it->live = true;
			std::cout << "Player " << it->id << " is alive!" << std::endl;
		}
	}
}

bool	Arena::checkLive()
{
	this->check_count += 1;
	if (this->check_count == NBR_LIVE)
	{
		this->check_count = 0;
		if (this->cycle_to_die - CYCLE_DELTA > 0)
			this->cycle_to_die -= CYCLE_DELTA;
	}
	for (std::list<Champion>::iterator it = champions.begin(); it != champions.end(); ++it)
	{
		if (!it->live)
		{
			std::cout << "Champion number " << it->id << " died by not saying live!" << std::endl;
			champions.erase(it);
		}
		else
			it->live = false;
		if (champions.size() == 1)
			return false;
	}
	return true;
}

bool	Arena::start(void)
{
	int	i = 0;
	while (42)
	{
		for (std::list<Champion>::iterator it = champions.begin(); it != champions.end(); ++it)
		{
			if (!it->doCycle(*this))
			{
				std::cout << "Champion number " << it->id << " died by doing shit!" << std::endl;
				champions.erase(it);
				if (champions.size() == 1)
					return true;
			}
		}
		++this->cycle_total;
		if (this->cycle_total % 30 == 0)
		{
			dumpArena();
			getchar();
		}
		if (this->cycle_total % this->cycle_to_die == 0)
			if (checkLive() == false)
				return true;
		if (champions.size() == 1)
			return true;
	}
	return true;
}

bool	Arena::setupArena(std::vector<std::string> &champions)
{
	int	i = 0;

	if (champions.size() > 6)
	{
		std::cout << "Too many champions";
		return false;
	}
	while (i != (1024 * 6))
		this->arena[i++] = 0x00;
	if (!loadChampions(champions))
		return false;
	return (this->champions.size() > 0);
}

std::vector<char> Arena::get(int offset, int size)
{
	int		i = 0;
	int		counter = offset;
	std::vector<char> data;

	while (offset > 1024 * 6)
		offset -= 1024 * 6;
	while (i != size)
	{
		data.push_back(this->arena[counter++]);
		++i;
		if (counter == 1024 * 6)
			counter = 0;
	}
	return data;
}

void Arena::dumpArena(void)
{
	int	i = 0;

	while (i != (1024 * 6))
	{
		printf("%02X ", this->arena[i]);
		if (i++ % 32 == 0 && i >= 32)
			std::cout << std::endl;
	}
	std::cout << "\n------------------------------------------------------------" << std::endl;
}

bool Arena::load(int offset, std::vector<char> &data)
{
	while (offset > 1024 * 6)
		offset -= 1024 * 6;
	int	i = offset;
	for (std::vector<char>::iterator it = data.begin(); it != data.end(); ++it)
	{
		this->arena[i++] = *it;
		if (i == 1024 * 6)
			i = 0;
	}
	return true;
}

bool Arena::load(int offset, std::string &data)
{
	while (offset > 1024 * 6)
		offset -= 1024 * 6;
	int	i = offset;
	int	counter = 0;
	while (counter != data.size())
	{
		this->arena[i++] = data[counter++];
		if (i == 1024 * 6)
			i = 0;
	}
	return true;
}

Arena::Arena()
{
}


Arena::~Arena()
{
}
