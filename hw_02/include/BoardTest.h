#pragma once
#include "Test.h"

class BoardTest : public Test
{
private:

	void test_game_in_progress();

	void can_move_1();
	void can_move_2();
	void can_move_3();

	void cant_move_1();
	void cant_move_2();
	void cant_move_3();
	void cant_move_4();
	void cant_move_5();

	void test_X_wins();
	void test_O_wins();
	void test_draw();
	void test_not_win_side_diagonal();
	void test_win_side_diagonal();
	void test_not_win_main_diagonal();
	void test_win_main_diagonal();
	void test_not_win_row();
	void test_win_row();
	void test_not_win_column();
	void test_win_column();

public:
	void run_all_tests() override;	
};