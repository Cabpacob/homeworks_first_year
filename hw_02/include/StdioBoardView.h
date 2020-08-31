#pragma once

#include "Board.h"

class StdioBoardView
{
public:
	StdioBoardView(Board &b, bool silent_mode);
	void run_game();
	void show_board();
private:
	void get_valid_coordinates(int32_t &x, int32_t &y);
	Board &b_;
	bool silent_mode_;
};
