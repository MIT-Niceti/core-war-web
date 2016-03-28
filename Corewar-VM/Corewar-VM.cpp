// Corewar-VM.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "Arena.h"

int _tmain(int argc, _TCHAR* argv[])
{
	Arena *arena = new Arena();
	std::vector<std::string> champions(2,"C:\\Users\\norman_e\\Pictures\\champion.txt");

	if (arena->setupArena(champions))
	{
		arena->start();
	}
	getchar();
	return 0;
}

