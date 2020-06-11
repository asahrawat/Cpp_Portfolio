// Amun Sahrawat
// COMP11
// HW7
// Board Class cpp


#include "game.h"
#include "board.h"
#include <fstream>
#include <iostream>
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

// The filename of the high scores file 
const char* FILENAME = "highscores.txt";


//Default Constructor
Game::Game()
{
	user_name = "";
	current_score = 0;
	high_scores = NULL;
	move = 'e';
	end_game = false;
	line_count = 0;
	
}


//Destructor
Game::~Game()
{
	if (high_scores != NULL)
	{
		delete []high_scores;

	}
}


void Game::read_move()
{
	if (move == 'w' || move == 'a' || move == 's' || move == 'd')
	{
		board_move();

	}
        else if (move == 'q')
	{
		end_game = true;
	}
	else if (move == 'h')
	{
		print_high_scores();
        }
	else
	{
		cout << "Please enter a valid move.\n";
        }
}


void Game::board_move()
{
	bool move_occurence;
        bool combo_occurence;

	//each movement returns the value of new tile(s) formed
	if (move == 'w')
		current_score += grid.move_up();
	
	else if (move == 'a')
		current_score += grid.move_left();

        else if (move == 's')
		current_score += grid.move_down();

        else if (move == 'd')
		current_score += grid.move_right();

	//check if either a shift or combination occured
	move_occurence = grid.get_move_happened();
        combo_occurence = grid.get_combine_happened();
	
	//only spawn new tile if shift or combination occured
        if(move_occurence == true || combo_occurence == true)
	{	
		grid.populate_board();
	}
}

string Game::print_first_score()
{
	ifstream infile;
	
	infile.open(FILENAME);

	string high_score;

	//if the file does not exist yet then the high score is 0
	if (!infile.is_open())
	{
		high_score = "0";
	}
	else
	{	
		string player, player_score;

		infile >> player;
		infile >> player_score;


		high_score = player_score;	
        }

	return high_score;
}




void Game::high_score_read()
{
        ifstream infile;
	infile.open(FILENAME);
	string line;
	line_count = 0;

	//if the file does not open then this is the first score
        //set up so that array can be allocated for just one score
	if (!infile.is_open())
		line_count = 1;

	//count the number of lines, including the sentinel, because new
	//score will add one more element to previous list
       	while(getline(infile, line))
		line_count++;

	infile.close();

	//allocate struct to hold all names and scores
	high_scores = new Player[line_count];

	infile.open(FILENAME);

		
	for (int i = 0; i < line_count - 1; i++)
	{
	        string player_name, player_score;

		infile >> high_scores[i].curr_name;
		infile >> player_score;

		// convert score strings to ints for sorting
	        int player_score_int = atoi(player_score.c_str());
                high_scores[i].score = player_score_int;
	}
	infile.close();
}


void Game::high_score_sort()
{
	//loop searches for appropriate position to insert new score
	for (int i = 0; i < line_count; i++)
	{
		if (i == line_count - 1)
		{
	        	high_scores[i].curr_name = user_name;
			high_scores[i].score = current_score;
		}
		if (high_scores[i].score < current_score)
		{
			//slide each name and score after the appropiate
			//positiondown one spot in the rankings
			for (int j = line_count - 1; j > i; j--)
			{
				high_scores[j].curr_name = 
                                        high_scores[j - 1].curr_name;

			        high_scores[j].score = 
                                        high_scores[j - 1].score;

			}

			high_scores[i].curr_name = user_name;
			high_scores[i].score = current_score;
			//exit search loop because appropriate position found
			break;
		}
	}

	//if first score in file, entire ray is just user_name and
	//current_score
        if (line_count == 1)
	{
		high_scores[0].curr_name = user_name;
		high_scores[0].score = current_score;
        }
}


void Game::high_score_write()
{
	ofstream outfile;
	outfile.open(FILENAME);

	//Read out each of the names and scores from the array into the file
	for (int i = 0; i < line_count; i++) 
	{
        	outfile << high_scores[i].curr_name;
		outfile << "     ";
		outfile << high_scores[i].score << endl;
	}

	// add a sentinel at the end
	outfile << "-1\n";

	outfile.close();
}

void Game::print_high_scores()
{
	int count = 0;	
	cout << "High Scores:\n";
        
	ifstream infile;
	infile.open(FILENAME);
	if (!infile.is_open())
		cout << "No high scores exist yet!\n";
	else
	{
		string curr_user;
		string user_score;		

		while (!infile.eof())
		{
			//ensure that the function only prints 5 entries max.
			if (count == 5)
				break;

			infile >> curr_user;
		        if (curr_user != "-1")
		        {
				infile >> user_score;

				cout << count + 1 << ". " << curr_user;
				cout << ", " <<  user_score << endl;
                        }
			count ++;
                }
        }

	infile.close();
}


bool Game::check_game_over()
{
	if (end_game == true)
		return true;
        else
	{
		bool moves_left;
		int spaces_left;

		//moves_possible returns a bool for if there are adjacent
		//squares with the same value (i.e. moves left)
		moves_left = grid.moves_possible();

		//moves_possible returns a bool for if there are any empty
		//squares in the board
		spaces_left = grid.count_clean_squares();		

		if (moves_left == false && spaces_left == 0)
                {	
	        	return true;
                }
        }

	return false;
}



void Game::run_game()
{
	cout << "Welcome to 2048!\n";
	cout << "Press 'h' for high scores and 'q' to quit at any point.\n";

	grid.starting_board();
        cout << "Starting Game! High score is ";
        cout << print_first_score() << endl;
	grid.print_board();	

	while (!end_game)
	{
		cout << "What direction would you like to move in ";
		cout << "(w/a/s/d)?\n";
                cin >> move;
		read_move();

		cout << "CURRENT SCORE: " << current_score << endl;
		grid.print_board();

		end_game = check_game_over();
	}
	
	cout << "What is your name?\n";
	cin >> user_name;

	high_score_read();
	high_score_sort();
        high_score_write();	

	cout << "Game over! Thanks for playing.\n";
	print_high_scores();
}

void Game::set_current_score(int s)
{
	s = current_score;
}

int Game::get_current_score()
{
	return current_score;
}


void Game::set_end_game(bool v)
{
	v = end_game;
}

bool Game::get_end_game()
{
	return end_game;
}


void Game::set_line_count(int z)
{
	z = line_count;
}

int Game::get_line_count()
{
	return line_count;
}
