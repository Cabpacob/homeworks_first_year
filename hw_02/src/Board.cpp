#include "Board.h"

Board::Board()
{
	field_.assign(Board_size, std::vector<box>(Board_size, box::empty));
	player_ = box::o;
}

bool out_of_board(int32_t x, int32_t y)
{
	return (x < 0 || y < 0 || x >= Board_size || y >= Board_size);
}

bool Board::can_move(int32_t x, int32_t y, box player)
{
	if(player_ != player)
		return 0;

	if(out_of_board(x, y))
		return 0;

	return (field_[x][y] == box::empty);
}

void Board::move(int32_t x, int32_t y, box player)
{
	if(can_move(x, y, player) && get_state() == game_state::unfinished)
	{
		field_[x][y] = player;
		player_ = (player_ == box::x ? box::o : box::x);
	}
}

box Board::check_win(int32_t x, int32_t y, int32_t delta_x, int32_t delta_y)
{
	if(out_of_board(x, y))
		return box::empty;
	if(field_[x][y] == box::empty)
		return box::empty;
	box candidate = field_[x][y]; 
	for(int32_t i = 0; i < To_win - 1; i++)
	{
		x += delta_x;
		y += delta_y;

		if(out_of_board(x, y) || field_[x][y] != candidate)
			return box::empty;
	}
	return candidate; 
}

game_state Board::get_state()
{
	std::vector<std::pair<int32_t, int32_t>> directions = {{1, 0}, {0, 1}, {1, 1}, {1, -1}};
	for(int32_t x = 0; x < Board_size; x++)
		for(int32_t y = 0; y < Board_size; y++)
		{
			for(auto direction : directions)
				if(check_win(x, y, direction.first, direction.second) != box::empty)
				{
					box result = check_win(x, y, direction.first, direction.second);
					return (result == box::x ? game_state::x_wins : game_state::o_wins); 
				}
		}

	int32_t empty_boxes = 0;
	for(int32_t x = 0; x < Board_size; x++)
		for(int32_t y = 0; y < Board_size; y++)
			if(field_[x][y] == box::empty)
				empty_boxes++;

	return (empty_boxes > 0 ? game_state::unfinished : game_state::draw);

}
