#include <iostream>
#include <unistd.h>
#include "NcursesBoardView.h"

NcursesBoardView::NcursesBoardView(Board &b) : b_(b) {};

void mark_win_boxes(std::vector<std::vector<bool>> &m, int32_t x, int32_t y, int32_t delta_x, int32_t delta_y)
{
	for(int32_t i = 0; i < To_win; i++)
	{
		m[x][y] = 1;
		x += delta_x;
		y += delta_y;
	}
}

void NcursesBoardView::show_board(int32_t curx, int32_t cury)
{

	clear();
	std::vector<std::vector<bool>> is_win(Board_size, std::vector<bool>(Board_size, 0));

	if(curx == -1 && cury == -1)
	{
		std::vector<std::pair<int32_t, int32_t>> directions = {{1, 0}, {0, 1}, {1, 1}, {1, -1}};
		for(int32_t x = 0; x < Board_size; x++)
			for(int32_t y = 0; y < Board_size; y++)
			{
				for(auto direction : directions)
					if(b_.check_win(x, y, direction.first, direction.second) != box::empty)
						mark_win_boxes(is_win, x, y, direction.first, direction.second);
			}
	}

	for(int32_t x = 0; x < Board_size; x++)
	{
		for(int32_t y = 0; y < Board_size; y++)
		{
			if(x == curx && y == cury)
			{
				if(b_.field_[x][y] == box::empty)
					addch((int32_t)b_.player_ | A_STANDOUT | A_UNDERLINE);
				else
					addch((char)b_.field_[x][y] | A_STANDOUT | A_UNDERLINE);
			}
			else
			{
				if(is_win[x][y])
				{
					addch((char)b_.field_[x][y] | A_STANDOUT);
				}
				else
				{
					addch((char)b_.field_[x][y]);
				}
			}
		}
		printw("\n");
	}
	refresh();
}

void NcursesBoardView::get_valid_coordinates(int32_t &x, int32_t &y)
{
	show_board(x, y);
	int32_t ch = getch();
	for(;ch != 10 || !b_.can_move(x, y, b_.player_);) //10 - enter
	{
		if(ch == 259) //259 - up
		{
			x = std::max(0, x - 1);
		}
		if(ch == 258) //258 - down
		{
			x = std::min(9, x + 1);
		}
		if(ch == 260) //260 - left
		{
			y = std::max(0, y - 1);
		}
		if(ch == 261) //261 - right
		{
			y = std::min(9, y + 1);
		}
		show_board(x, y);
		ch = getch();
	}
}


void NcursesBoardView::run_game()
{
	initscr();
	curs_set(0);
    keypad(stdscr, true);
    noecho();

	int32_t x = 0, y = 0;
	for(;b_.get_state() == game_state::unfinished;)
	{
		show_board(x, y);
		get_valid_coordinates(x, y);
		b_.move(x, y, b_.player_);
	}

	show_board(-1, -1);
	auto result = b_.get_state();
	if(result == game_state::draw)
	{
		printw("Draw.\n");
	}
	else
	{
		printw((result == game_state::x_wins ? "X" : "O"));
		printw(" wins!\n");
	}

	refresh();
	sleep(10);
    endwin(); 
}

