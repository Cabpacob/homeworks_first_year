#include "Board.h" 
#include "BoardTest.h"

void BoardTest::test_game_in_progress()
{
	Board b;
	b.move(0, 0, box::o);
	b.move(1, 1, box::x);

	b.move(1, 1, box::x);
	b.move(2, 1, box::x);

	DO_CHECK(b.get_state() == game_state::unfinished);
}


void BoardTest::can_move_1()
{
	Board b;

	DO_CHECK(b.can_move(0, 0, box::o));
}

void BoardTest::can_move_2()
{
	Board b;

	b.move(0, 0, box::o);
	DO_CHECK(b.can_move(1, 1, box::x));
}

void BoardTest::can_move_3()
{
	Board b;

	b.move(0, 0, box::o);
	b.move(1, 0, box::x);

	DO_CHECK(b.can_move(1, 1, box::o));
}

void BoardTest::cant_move_1()
{
	Board b;

	DO_CHECK(!b.can_move(10, 10, box::o));
}

void BoardTest::cant_move_2()
{
	Board b;

	b.move(0, 0, box::o);
	DO_CHECK(!b.can_move(0, 0, box::x));
}

void BoardTest::cant_move_3()
{
	Board b;

	b.move(0, 0, box::o);

	DO_CHECK(!b.can_move(1, 1, box::o));
}

void BoardTest::cant_move_4()
{
	Board b;

	b.move(0, 0, box::o);
	b.move(1, 0, box::x);

	DO_CHECK(!b.can_move(1, 0, box::o));
}

void BoardTest::cant_move_5()
{
	Board b;

	b.move(0, 0, box::o);
	b.move(1, 0, box::x);

	DO_CHECK(!b.can_move(0, 0, box::o));
}

void BoardTest::test_X_wins()
{
	Board b;

	b.move(0, 0, box::o);
	b.move(1, 1, box::x);

	b.move(0, 1, box::o);
	b.move(2, 2, box::x);

	b.move(0, 2, box::o);
	b.move(3, 3, box::x);

	b.move(0, 3, box::o);
	b.move(4, 4, box::x);

	b.move(0, 6, box::o);
	b.move(5, 5, box::x);

	DO_CHECK(b.get_state() == game_state::x_wins);
}

void BoardTest::test_O_wins()
{
	Board b;

	b.move(0, 0, box::o);
	b.move(1, 1, box::x);

	b.move(0, 1, box::o);
	b.move(2, 2, box::x);

	b.move(0, 2, box::o);
	b.move(3, 3, box::x);

	b.move(0, 3, box::o);
	b.move(4, 4, box::x);

	b.move(0, 4, box::o);

	DO_CHECK(b.get_state() == game_state::o_wins);
}

void BoardTest::test_draw()
{
	Board b;

	for(int i = 0; i < 10; i++)
		if(i % 4 < 2)
		{
			b.move(0, i, box::o);
			b.move(1, i, box::x);

			b.move(2, i, box::o);
			b.move(3, i, box::x);

			b.move(4, i, box::o);
			b.move(5, i, box::x);

			b.move(6, i, box::o);
			b.move(7, i, box::x);

			b.move(8, i, box::o);
			b.move(9, i, box::x);
		}
		else
		{
			b.move(1, i, box::o);
			b.move(0, i, box::x);

			b.move(3, i, box::o);
			b.move(2, i, box::x);

			b.move(5, i, box::o);
			b.move(4, i, box::x);

			b.move(7, i, box::o);
			b.move(6, i, box::x);

			b.move(9, i, box::o);
			b.move(8, i, box::x);
		}

	DO_CHECK(b.get_state() == game_state::draw);
}

void BoardTest::test_not_win_side_diagonal()
{
	/*
	 .......O..
	 ......O...
	 .....O....
	 ....O.....
	 ........X.
	 ..O..X.X..
	 .OX...X...
	 O.........
	 ..X.X.....
	 ..........
	*/
	Board b;
	b.move(0, 7, box::o);
	b.move(4, 8, box::x);
	b.move(1, 6, box::o);
	b.move(5, 5, box::x);
	b.move(2, 5, box::o);
	b.move(5, 7, box::x);
	b.move(3, 4, box::o);
	b.move(6, 2, box::x);
	b.move(5, 2, box::o);
	b.move(6, 6, box::x);
	b.move(6, 1, box::o);
	b.move(8, 2, box::x);
	b.move(7, 0, box::o);
	b.move(8, 4, box::x);

	DO_CHECK(b.get_state() == game_state::unfinished);
}

void BoardTest::test_win_side_diagonal()
{
	/*
	 .......O..
	 ......O...
	 .....O....
	 ....O.....
	 ...O....X.
	 ..O..X.X..
	 .OX...X...
	 O.........
	 ..X.X.....
	 ..........
	*/
	Board b;
	b.move(0, 7, box::o);
	b.move(4, 8, box::x);
	b.move(1, 6, box::o);
	b.move(5, 5, box::x);
	b.move(2, 5, box::o);
	b.move(5, 7, box::x);
	b.move(3, 4, box::o);
	b.move(6, 2, box::x);
	b.move(5, 2, box::o);
	b.move(6, 6, box::x);
	b.move(6, 1, box::o);
	b.move(8, 2, box::x);
	b.move(7, 0, box::o);
	b.move(8, 4, box::x);
	b.move(4, 3, box::o);

	DO_CHECK(b.get_state() == game_state::o_wins);
}

void BoardTest::test_not_win_main_diagonal()
{
	Board b;
	b.move(0, 0, box::o);
	b.move(1, 0, box::x);
	b.move(1, 1, box::o);
	b.move(2, 0, box::x);
	b.move(2, 2, box::o);
	b.move(9, 8, box::x);
	b.move(3, 3, box::o);
	b.move(4, 7, box::x);

	b.move(5, 5, box::o);
	b.move(1, 6, box::x);
	b.move(6, 6, box::o);
	b.move(2, 7, box::x);
	b.move(7, 7, box::o);
	b.move(8, 7, box::x);
	b.move(8, 8, box::o);
	b.move(9, 7, box::x);

	DO_CHECK(b.get_state() == game_state::unfinished);
}

void BoardTest::test_win_main_diagonal()
{
	Board b;
	b.move(0, 0, box::o);
	b.move(1, 0, box::x);
	b.move(1, 1, box::o);
	b.move(2, 0, box::x);
	b.move(2, 2, box::o);
	b.move(9, 8, box::x);
	b.move(3, 3, box::o);
	b.move(4, 7, box::x);

	b.move(5, 5, box::o);
	b.move(1, 6, box::x);
	b.move(6, 6, box::o);
	b.move(2, 7, box::x);
	b.move(7, 7, box::o);
	b.move(8, 7, box::x);
	b.move(8, 8, box::o);
	b.move(9, 7, box::x);

	b.move(4, 4, box::o);

	DO_CHECK(b.get_state() == game_state::o_wins);
}

void BoardTest::test_not_win_row()
{
	Board b;
	b.move(0, 0, box::o);
	b.move(2, 6, box::x);
	b.move(0, 1, box::o);
	b.move(3, 4, box::x);
	b.move(0, 2, box::o);
	b.move(5, 3, box::x);
	b.move(0, 3, box::o);
	b.move(5, 6, box::x);
	b.move(0, 5, box::o);
	b.move(7, 1, box::x);
	b.move(0, 6, box::o);
	b.move(7, 5, box::x);
	b.move(0, 7, box::o);
	b.move(8, 3, box::x);
	b.move(0, 8, box::o);
	b.move(8, 7, box::x);

	DO_CHECK(b.get_state() == game_state::unfinished);
}

void BoardTest::test_win_row()
{
	Board b;
	b.move(0, 0, box::o);
	b.move(2, 6, box::x);
	b.move(0, 1, box::o);
	b.move(3, 4, box::x);
	b.move(0, 2, box::o);
	b.move(5, 3, box::x);
	b.move(0, 3, box::o);
	b.move(5, 6, box::x);
	b.move(0, 5, box::o);
	b.move(7, 1, box::x);
	b.move(0, 6, box::o);
	b.move(7, 5, box::x);
	b.move(0, 7, box::o);
	b.move(8, 3, box::x);
	b.move(0, 8, box::o);
	b.move(8, 7, box::x);

	b.move(0, 4, box::o);

	DO_CHECK(b.get_state() == game_state::o_wins);
}

void BoardTest::test_not_win_column()
{
	Board b;
	b.move(0, 0, box::o);
	b.move(2, 6, box::x);
	b.move(1, 0, box::o);
	b.move(3, 4, box::x);
	b.move(2, 0, box::o);
	b.move(5, 3, box::x);
	b.move(3, 0, box::o);
	b.move(5, 6, box::x);
	b.move(5, 0, box::o);
	b.move(7, 1, box::x);
	b.move(6, 0, box::o);
	b.move(7, 5, box::x);
	b.move(7, 0, box::o);
	b.move(8, 3, box::x);
	b.move(8, 0, box::o);
	b.move(8, 7, box::x);

	DO_CHECK(b.get_state() == game_state::unfinished);
}

void BoardTest::test_win_column()
{
	Board b;
	b.move(0, 0, box::o);
	b.move(2, 6, box::x);
	b.move(1, 0, box::o);
	b.move(3, 4, box::x);
	b.move(2, 0, box::o);
	b.move(5, 3, box::x);
	b.move(3, 0, box::o);
	b.move(5, 6, box::x);
	b.move(5, 0, box::o);
	b.move(7, 1, box::x);
	b.move(6, 0, box::o);
	b.move(7, 5, box::x);
	b.move(7, 0, box::o);
	b.move(8, 3, box::x);
	b.move(8, 0, box::o);
	b.move(8, 7, box::x);

	b.move(4, 0, box::o);

	DO_CHECK(b.get_state() == game_state::o_wins);
}

void BoardTest::run_all_tests()
{
	test_game_in_progress();

	can_move_1();
	can_move_2();
	can_move_3();

	cant_move_1();
	cant_move_2();
	cant_move_3();
	cant_move_4();
	cant_move_5();

	test_X_wins();
	test_O_wins();
	test_draw();

	test_not_win_side_diagonal();
	test_win_side_diagonal();
	test_not_win_main_diagonal();
	test_win_main_diagonal();
	test_not_win_row();
	test_win_row();
	test_not_win_column();
	test_win_column();
}