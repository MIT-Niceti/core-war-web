// Corewar-VM.cpp�: d�finit le point d'entr�e pour l'application console.
//

#include "stdafx.h"
#include "Arena.h"

int startMachine(std::vector<std::string> &champions)
{
	Arena *arena = new Arena();
	std::vector<std::string> championss(2,"C:\\Users\\norman_e\\Pictures\\champion.txt");

	if (arena->setupArena(championss))
		arena->start();
	return 0;
}