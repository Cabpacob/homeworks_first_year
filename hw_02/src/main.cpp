#include <iostream>
#include <cstring>
#include "Board.h"
#include "StdioBoardView.h"
#include "NcursesBoardView.h"

int main(int argc, char *argv[])
{
	if(argc == 1 || (argc > 1 && !strcmp(argv[1], "silent")))
	{
		bool silent = 0;
		if(argc > 1 && !strcmp(argv[1], "silent"))
			silent = 1;
		Board b;
		StdioBoardView sbv(b, silent);
		sbv.run_game();
	}
	else if(argc > 1 && !strcmp(argv[1], "curses"))
	{
		Board b;
		NcursesBoardView nbv(b);
		nbv.run_game();
	}
	else
	{
		std::cout << "Invalid flag" << std::endl;
	}
	return 0;

}
