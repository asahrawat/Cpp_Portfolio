#include "board.h"
#include <iostream>

using namespace std;



int main()
{
	Board board1;
	
	board1.starting_board();
	board1.print_board();
	
	for(int i = 1; i < 10; i++)
        {
		
		board1.count_clean_squares();
		int step;
		cout << "move\n";
		cin >> step;

		board1.move_left();
		board1.populate_board();
		board1.print_board();

	        board1.count_clean_squares();
		cout << "move\n";
		cin >> step;

		step++;

		board1.move_right();
		board1.populate_board();
		board1.print_board();

 		board1.count_clean_squares();
		cout << "move\n";
		cin >> step;

		step++;

		board1.move_up();
		board1.populate_board();
		board1.print_board();

 		board1.count_clean_squares();
		cout << "move\n";
		cin >> step;

		step++;

		board1.move_down();
		board1.populate_board();
		board1.print_board();


	}




	return 0;
}
