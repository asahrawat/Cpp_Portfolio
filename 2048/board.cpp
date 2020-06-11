// Amun Sahrawat
// COMP11
// HW7
// Board Class cpp


#include "board.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
using namespace std;

//Default constructor
Board::Board()
{
	dimen = 0;
	clean_squares = 0;
	ray = NULL;
}

//Destructor
Board::~Board()
{
	if (ray != NULL)
	{	
		for (int i = 0; i < dimen; i++)
		{
			delete[] ray[i];
		}

		delete []ray;
        }
}

void Board::starting_board()
{
	allocate_board();
	//uncomment (and comment out above) for extra credit
	//extra_allocate_board();
	populate_empty_board();
}

void Board::allocate_board()
{
	int size;
	
	cout << "How many rows and columns do you want in your board?\n";
	cin >> size;

	set_dimen(size);

	//allocate array of user's specified size
	ray = new int * [size];

        //in each element of ray, allocate an array of user's specified size
        //creates 2-dimensional array for board
	for (int i = 0; i < size; i++)
		ray[i] = new int[size];

}

void Board::extra_allocate_board()
{
	char difficulty;
	int size;
	
	do
        {
		cout << "What difficult level would you like to play?\n";
		cout << "Easy (e), medium (m), or hard (h)\n";
		cin >> difficulty;

		// set board size according to difficulty level
		if (difficulty == 'e')
			size = 5;

		if (difficulty == 'm')
			size = 4;

	        if (difficulty == 'h')
			size = 3;
        }while (difficulty != 'e' && difficulty != 'm' && difficulty != 'h');

	set_dimen(size);

	//allocate array of user's specified size
	ray = new int * [size];

        //in each element of ray, allocate an array of user's specified size
        //creates 2-dimensional array for board
	for (int i = 0; i < size; i++)
		ray[i] = new int[size];

}


void Board::populate_empty_board()
{
	srand(time(NULL));
	int k, l, m, n;
 
	// choose coordinates for first tile
	k = rand() % dimen;
	l = rand() % dimen;
       
	// choose coordinates for second tile. Check second tile is at
	// different position from first tile.
        do
	{
		m = rand() % dimen;
		n = rand() % dimen;		
        } while (m == k && n == l);

        ray[k][l] = 2;
	ray[m][n] = 2;


	for(int i = 0; i < dimen; i++)
	{
		for(int j = 0; j < dimen; j++)
		{
			if (ray[i][j] != 2)
                        {
				ray[i][j] = 0;
			}
		}
	}
	// fill the rest of the board with zeroes
	fill_zeroes();
}


void Board::fill_zeroes()
{
	for(int i = 0; i < dimen; i++)
	{
		for(int j = 0; j < dimen; j++)
		{
			if (ray[i][j] != 2)
                        {
				ray[i][j] = 0;
			}
		}
	}
}


int Board::count_clean_squares()
{
	int blanks = 0;

	// cycle through all tiles and count up the number of 0's
	for (int i = 0; i < dimen; i++)
	{
		for(int j = 0; j < dimen; j++)
		{
			if (ray[i][j] == 0)
			{
				blanks++;	
			}
		}
	}

	set_clean_squares(blanks);

	return blanks;	

}


void Board::populate_board()
{	
	int i, j, chance;

	// assign coordinates for new tile and make sure tile is on boundary
	do
	{
		i = rand() % dimen;
		j = rand() % dimen;
        }while (ray[i][j] != 0 || (i != 0 && j != 0 && i != dimen - 1
	        	 && j != dimen - 1));

        // 10 % chance that new tile is a 4
        chance = rand() % 10 + 1;
        if (chance == 1)
	{
		ray[i][j] = 4;
	}
	else
	{
		ray[i][j] = 2;
	}

}

void Board::print_board()
{
	// cycle through each element of board array
	for (int i = 0; i < dimen; i++)
	{
		for (int j = 0; j < dimen; j++)
		{
			// line up all numbers by printing a different
		        // number of spaces depending on size of number
			if (ray[i][j] == 0)
				cout << EMPTY_TILE << "    ";

			if (ray[i][j] < 10 && ray[i][j] != 0)
				cout << ray[i][j] << "    ";

			if (ray[i][j] >= 10 && ray[i][j] < 100)
				cout << ray[i][j] << "   ";

			if (ray[i][j] >= 100 && ray[i][j] < 1000)
				cout << ray[i][j] << "  ";

                        if (ray[i][j] >= 1000 && ray[i][j] < 10000)
				cout << ray[i][j] << " ";
                }
		// after each row start a new line with appropriate spacing
		cout << endl << endl;
        }
}



int Board::combine_tilesh(int n, int o, int p)
{
	// set one coordinate to the sum of the two tiles and the other to 0
	int sum;
	sum = ray[n][o] + ray[n][p];
	ray[n][o] = sum;
	ray[n][p] = 0;
	
	// sum is the value of "new tile" formed
	return sum;
}


int Board::combine_tilesv(int q, int r, int s)
{
	// set one coordinate to the sum of the two tiles and the other to 0
	int sum;
	sum = ray[q][r] + ray[s][r];
	ray[q][r] = sum;
	ray[s][r] = 0;
	
	// need different function because row is constant horizontally and
        // column is constant vertically
	return sum;
}

void Board::slide_horiz(int a, int b, int c)
{
	// simple bubble sort. Switch two values in array
	int temp;
      	temp = ray[a][c];
	ray[a][c] = ray[a][b];
	ray[a][b] = temp;
}


void Board::slide_vert(int d, int e, int f)
{
	// simple bubble sort. Switch two values in array
	int temp;
	temp = ray[f][e];
        ray[f][e] = ray[d][e];
        ray[d][e] = temp;
}

int Board::move_left()
{
	int score_add = 0;
	combine_happened = false;

	for (int j = 0; j < dimen - 1; j++)
        {
		for (int i = 0; i < dimen; i++)
		{
			// check next tile in given direction
			int k = j+1;
			// check for combination possibility
                        while (ray[i][k] == 0 || ray[i][k] == ray[i][j])
			{
				if (ray[i][j] == ray[i][k])
				{
					score_add += combine_tilesh(i, j, k);
					// 0's will combine with other 0's
					// but that's not a movement
					if(ray[i][j] != 0)
				        	combine_happened = true;
				        // break after combination has
					// occured to make sure tile does not
					// combine with any other tile
					break;
                                }

				// if target tile is 0 then current tile
				// could still combine with next tile in
				// given direction with shift
				if (ray[i][k] == 0)
					k++;
				// avoid seg fault b/c out of bounds
				if (k == dimen)
					break;
			}
		}
        }
	// shift tiles after all combinations
	left_shift();

	return score_add;
}

void Board::left_shift()
{
	move_happened = false;
	
	for (int j = 0; j < dimen; j++)
        {
		for (int i = 0; i < dimen; i++)
		{
			int k = j + 1;
			// start shifting tiles from next tile in 
			// appropriate direction
			while(ray[i][j] == 0 && k < dimen)
			{
				slide_horiz(i, j, k);
				// 0's will swap with other 0's but a move
			        // did not happen then
				if (ray[i][j] != 0)
					move_happened = true;
				k++;	
			}
		}
        }
}


int Board::move_right()
{
	int score_add = 0;
	combine_happened = false;

	for (int j = dimen - 1; j >= 1; j--)
        {
		for (int i = 0; i < dimen; i++)
		{
			// check next tile in given direction
			int k = j - 1;
			// check for combination possibility
                        while (ray[i][k] == 0 || ray[i][k] == ray[i][j])
			{
				// combine identical adjacent tiles
				if (ray[i][j] == ray[i][k])
				{
					score_add += combine_tilesh(i, j, k);
					// 0's will combine with other 0's
					// but that's not a movement
					if(ray[i][j] != 0)
						combine_happened = true;
				        // break after combination has
					// occured to make sure tile does not
					// combine with any other tile
					break;
                                }

				// if target tile is 0 then current tile
				// could still combine with next tile in
				// given direction with shift
				if (ray[i][k] == 0)
					k--;
				// avoid seg fault b/c out of bounds
				if (k < 0)
					break;
			}			
		}
        }
	// shift tiles after all combinations
	right_shift();

	return score_add;	
}

void Board::right_shift()
{
	move_happened = false;

	for (int j = dimen - 1; j >= 0; j--)
        {
		for (int i = 0; i < dimen; i++)
		{
			int k = j - 1;
			// start shifting tiles from next tile in 
			// appropriate direction
			while(ray[i][j] == 0 && k >= 0)
			{
				slide_horiz(i, j, k);
				// 0's will swap with other 0's but a move
			        // did not happen then
				if (ray[i][j] != 0)
				        move_happened = true;
				k--;	
			}      
                }
        }
}

int Board::move_up()
{
	int score_add = 0;
	combine_happened = false;

	for (int i = 0; i < dimen - 1; i++)
        {
		for (int j = 0; j < dimen; j++)
		{
			// check next tile in given direction
			int k = i + 1;
			// check for combination possibility
                        while ( ray[k][j] == 0 || ray[k][j] == ray[i][j])
			{
				// combine identical adjacent tiles
				if (ray[i][j] == ray[k][j])
				{
					score_add += combine_tilesv(i, j, k);
					// 0's will combine with other 0's
					// but that's not a movement
					if(ray[i][j] != 0)
						combine_happened = true;
				        // break after combination has
					// occured to make sure tile does not
					// combine with any other tile
					break;
                                }

				// if target tile is 0 then current tile
				// could still combine with next tile in
				// given direction with shift
				if (ray[k][j] == 0)
					k++;
				// avoid seg fault b/c out of bounds
				if (k == dimen)
					break;
			}
		}
        }
	// shift tiles after all combinations
	up_shift();

	return score_add;
}

void Board::up_shift()
{
	move_happened = false;

	for (int i = 0; i < dimen; i++)
        {
		for (int j = 0; j < dimen; j++)
		{
			int k = i + 1;
			// start shifting tiles from next tile in 
			// appropriate direction
			while(ray[i][j] == 0 && k < dimen)
			{
				slide_vert(i, j, k);
				// 0's will swap with other 0's but a move
			        // did not happen then
				if (ray[i][j] != 0)
					move_happened = true;
				k++;	
			}
                }
        }
}

int Board::move_down()
{
	int score_add = 0;
	combine_happened = false;

	for (int i = dimen - 1; i >= 1; i--)
        {
		for (int j = 0; j < dimen; j++)
		{
			// check next tile in given direction
			int k = i - 1;
			// check for combination possibility
                        while ( ray[k][j] == 0 || ray[k][j] == ray[i][j])
			{
				if (ray[i][j] == ray[k][j])
				{
					score_add += combine_tilesv(i, j, k);
					// 0's will combine with other 0's
					// but that's not a movement
					if(ray[i][j] != 0)
						combine_happened = true;
				        // break after combination has
					// occured to make sure tile does not
					// combine with any other tile
					break;
                                }

				// if target tile is 0 then current tile
				// could still combine with next tile in
				// given direction with shift
				if (ray[k][j] == 0)
					k--;
				// avoid seg fault b/c out of bounds
				if (k < 0)
					break;
			}			
		}
        }
	// shift tiles after all combinations
	down_shift();
	
	return score_add;	
}

void Board::down_shift()
{
	move_happened = false;

	for (int i = dimen - 1; i >= 0; i--)
        {
		for (int j = 0; j < dimen; j++)
		{
			int k = i - 1;
			// start shifting tiles from next tile in 
			// appropriate direction
			while(ray[i][j] == 0 && k >= 0)
			{
				slide_vert(i, j, k);
				// 0's will swap with other 0's but a move
			        // did not happen then
				if (ray[i][j] != 0)
					move_happened = true;
				k--;	
			}       
                }
        }
}

bool Board::moves_possible()
{
	bool poss_moves = false;

	// check if adjacent tiles, horizontally, are identical
	for (int i = 0; i < dimen; i++)
	{
		for (int j = 0; j < dimen - 1; j++)
		{
			if (ray[i][j] == ray [i][j + 1])
                                poss_moves = true;
                }
        }

	// check if adjacent tiles, vertically, are identical
	for (int j = 0; j < dimen; j++)
        {
		for (int i = 0; i < dimen - 1; i++)
                {
			if (ray[i][j] == ray [i + 1][j])
				poss_moves = true;
                }
        }

	return poss_moves;
}

void Board::set_move_happened(bool t)
{
	move_happened = t;

}

bool Board::get_move_happened()
{
	return move_happened;
}

void Board::set_combine_happened(bool f)
{
	combine_happened = f;

}

bool Board::get_combine_happened()
{
	return combine_happened;
}

void Board::set_dimen(int l)
{
	if (l >= 1 && l <= MAX_DIMEN)
		dimen = l;
}

int Board::get_dimen()
{
	return dimen;
}


void Board::set_clean_squares(int m)
{
        clean_squares = m;
}

int Board::get_clean_squares()
{
	return clean_squares;
}
