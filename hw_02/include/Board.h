#include <vector>
#include <cstdint>
#pragma once

const int32_t Board_size = 10;
const int32_t To_win = 5;

enum class game_state {unfinished, x_wins, o_wins, draw};

enum class box {empty = '.', x = 'X', o = 'O'};

class Board
{
public:
	Board();
	void move(int32_t x, int32_t y, box current_player);
	game_state get_state();
	bool can_move(int32_t x, int32_t y, box player);
	std::vector<std::vector<box>> field_; 
	box player_;
	
	box check_win(int32_t x, int32_t y, int32_t delta_x, int32_t delta_y); //not private for NcursesBoardView
}; 

bool out_of_board(int32_t x, int32_t y);
