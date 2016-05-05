// Corewar-VM.cpp�: d�finit le point d'entr�e pour l'application console.
//

#include "stdafx.h"
#include "Arena.h"

std::string startMachine(std::vector<std::string> &champions)
{
	Arena *arena = new Arena();
	std::vector<std::string> championss;

	std::cout << "BEGIN LOAD" << std::endl;
	championss.push_back("C:\\Users\\norman_e\\Pictures\\champion.txt");
	championss.push_back("C:\\Users\\norman_e\\Pictures\\forker.txt");
	std::cout << "DONE LOAD" << std::endl;
	if (arena->setupArena(championss))
		return (arena->start());
	return "";
}
