#pragma once

#include "Board.h"

#include <curses.h>
#include <vector>

class NcursesBoardView
{
public:
	NcursesBoardView(Board &b);
	void run_game();
	void show_board(int32_t curx, int32_t cury);
private:
	void get_valid_coordinates(int32_t &x, int32_t &y);
	Board &b_;
};

void mark_win_boxes(std::vector<std::vector<bool>> &m, int32_t x, int32_t y, int32_t delta_x, int32_t delta_y);