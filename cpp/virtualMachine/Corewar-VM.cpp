// Corewar-VM.cpp�: d�finit le point d'entr�e pour l'application console.
//

#include "stdafx.h"
#include "Arena.h"

std::string startMachine(std::vector<std::string> &champions)
{
	Arena *arena = new Arena();
	std::vector<std::string> championss;

/*	std::cout << "BEGIN LOAD" << std::endl;
	championss.push_back("C:\\Users\\norman_e\\Pictures\\reference_champion.out");
	championss.push_back("C:\\Users\\norman_e\\Pictures\\forker.out");*/
	std::cout << "DONE LOAD" << std::endl;
	if (arena->setupArena(champions))
		return (arena->start());
	std::cout << "DONE GAME" << std::endl;
	return "";
}
