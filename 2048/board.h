// Amun Sahrawat
// COMP11
// HW6
// Board Class Header



#include <iostream>
#include <string>
using namespace std;

#ifndef BOARD_H_
#define BOARD_H_

// Blank squares in the printed board will be represented by an 'X' char
const char EMPTY_TILE = 'X';

// Maximum dimension for board is 10 by 10
const int MAX_DIMEN = 10;

class Board
{
	private:
		// Attributes of a board
		
		// Dimensions of board
		int dimen;

		// Number of empty spaces on the board
		int clean_squares;

		// Dynamically allocated 2D array to hold all values and
		// positions that are on the board
		int **ray;
	
		// Boolean to check if any tiles shifted, regardless of
		// whether a combination was involved or not
		bool move_happened;
		
		// Boolean to check if any combination of tiles occured
		bool combine_happened;

	public:
		// Constructor for Board class
		Board();
		// Deconstructor for Board class	
		~Board();


		// Setters and Getters 	

		// Parameters: int (dimen value)
		// Returns: nothing
		// Does: sets value of dimen attribute
		void set_dimen(int);

		// Parameters: int (clean squares value)
		// Returns: nothing
		// Does: sets value of clean_squares attribute		
		void set_clean_squares(int);

	        // Parameters: boolean
		// Returns: nothing
		// Does: sets the value of move_happened attribute
		void set_move_happened(bool);

	        // Parameters: boolean
		// Returns: nothing
		// Does: sets the value of combine_happened attribute
		void set_combine_happened(bool);

		// Parameters: none
		// Returns: value of dimen attribute
		// Does: gets value of dimen attribute
		int get_dimen();

		// Parameters: none
		// Returns: value of clean_squares attribute
		// Does: gets value of clean_squares attribute
		int get_clean_squares();

		// Parameters: none
		// Returns: value of move_happened attribute
		// Does: gets value of move_happened attribute
		bool get_move_happened();

		// Parameters: none
	        // Returns: value of combine_happened attribute
		// Does: gets value of combine_happened attribute
		bool get_combine_happened();



		// Parameters: nothing
		// uses 2D array, 'ray' attribute
		// Returns: points added as a result of move (int)
      		// Does: moves entire board to the left, calls combine tiles
		// function first then shift function
                int move_left();
		
		// Parameters: nothing
		// Returns: nothing
		// Does: shifts each element in the board as far left as it
		// can go
     		void left_shift();

		// Parameters: nothing
		// uses 2D array, 'ray' attribute
		// Returns: points added as a result of move (int)
      		// Does: moves entire board to the left, calls combine tiles
		// function first then shift function
                int move_right();

		// Parameters: nothing
		// Returns: nothing
		// Does: shifts each element in the board as far right as it
		// can go
     		void right_shift();

		// Parameters: nothing
		// uses 2D array, 'ray' attribute
		// Returns: points added as a result of move (int)
      		// Does: moves entire board to the left, calls combine tiles
		// function first then shift function
                int move_up();

		// Parameters: nothing
		// Returns: nothing
		// Does: shifts each element in the board as far up as it
		// can go
     		void up_shift();

		// Parameters: nothing
		// uses 2D array, 'ray' attribute
		// Returns: points added as a result of move (int)
      		// Does: moves entire board to the left, calls combine tiles
		// function first then shift function
                int move_down();

		// Parameters: nothing
		// Returns: nothing
		// Does: shifts each element in the board as far down as it
		// can go
     		void down_shift();


		// Parameters: the values of two tiles to be combined
		// Returns: sum of the two tiles
		// Does: sums the values of two tiles (horizontally)
		int combine_tilesh(int, int, int);

		// Parameters: the values of two tiles to be combined
		// Returns: sum of the two tiles
		// Does: sums the values of two tiles (vertically)
		int combine_tilesv(int, int, int);


		// Parameters: Coordinates of tiles to be swapped (int)
		// Returns: nothing
		// Does: Switches the positions of two tiles (horizontally)
		void slide_horiz(int, int, int);



		// Parameters: Coordinates of tiles to be swapped (int)
		// Returns: nothing
		// Does: Switches the positions of two tiles (vertically)
                void slide_vert(int, int, int);


		// Parameters: none
		// uses 2D array, 'ray' attribute
		// Returns: current number of empty spaces on board
                // does: Count spaces in array with 0's in them
                int count_clean_squares();

		// Parameters: none
		// uses 2D array, 'ray' attribute
		// Returns: nothing
		// Does: Prints the current board as chars
                void print_board();

		// Parameters: nothing
		// uses dimen attribute, 'ray' attribute
		// Returns: nothing
		// Does: Makes Board ready to play. 
		// places 2 number 2's in empty board and places 0's in all
		// other empty spaces.
		void populate_empty_board();

		// Parameters: nothing
		// Returns: nothing
		// Does: fills the rest of the board with 0's in th beginning
		void fill_zeroes();

		// Parameters: nothing
		// uses 2D array, 'ray' attribute
		// Returns: nothing
      		// Does: places random number in current board. Called after
		// each move
		void populate_board();

		
		// Parameters: nothing
		// Returns: nothing
		// Does: Prompts user for number of rows/columns in board
		// and allocates memory for 2D array of board
		void allocate_board();
		
//*****************************Extra Credit Function************************
		// Parameters: nothing
		// Returns: nothing
		// Does: Prompts the user for a level of Difficulty
		void extra_allocate_board();
//**************************************************************************

		// Parameters: nothing
		// Returns: nothing
		// Does: allocates memory for board and populates empty board
		void starting_board();

		// Parameters: nothing
		// Returns: bool for if there are possible moves left or not
		// Does: sees if adjacent tiles are identical (i.e. can be
		// combined) and, as a consequence, if there are moves left
		bool moves_possible();

};

#endif

