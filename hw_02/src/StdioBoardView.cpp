#include <iostream>
#include "StdioBoardView.h"

StdioBoardView::StdioBoardView(Board &b, bool silent_mode = 0) : b_(b), silent_mode_(silent_mode) {};

void StdioBoardView::show_board()
{
	std::cout << std::endl;
	for(auto line : b_.field_)
	{
		for(auto box : line)
			std::cout << (char)box;
		std::cout << std::endl;
	}
}

void StdioBoardView::get_valid_coordinates(int32_t &x, int32_t &y)
{
	int32_t read = 0;
	for(;;)
	{
		std::cout << (char)b_.player_ << " move: ";
		std::string s;
		getline(std::cin, s);
		char third;
		read = sscanf(s.c_str(), "%d %d %c", &x, &y, &third);
		if((read == 2) && ((x == -1 && y == -1) || (b_.can_move(x, y, b_.player_) && s.find('-') == std::string::npos)))
			break;
		std::cout << "Bad move!" << std::endl;
	}
}


void StdioBoardView::run_game()
{
	for(;b_.get_state() == game_state::unfinished;)
	{
		if(!silent_mode_)
			show_board();
		int32_t x, y;
		get_valid_coordinates(x, y);
		if(x == -1 && y == -1)
			return;
		b_.move(x, y, b_.player_);
	}

	show_board();
	auto result = b_.get_state();
	if(result == game_state::draw)
	{
		std::cout << "Draw." << std::endl;
	}
	else
	{
		std::cout << (result == game_state::x_wins ? 'X' : 'O') << " wins!" << std::endl;
	}
}
