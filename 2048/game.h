// Amun Sahrawat
// COMP11
// HW6
// Game Class Header

// Sign off: Professor Strange 4/11/17

#include <string>
#include "board.h"

using namespace std;

#ifndef GAME_H_
#define GAME_H_


class Game
{
        private:

		//Attributes of a game

		// current user's name
		string user_name;
		
		// keeps track of score throughout game
        	int current_score; 

		// user's decision, or move
		char move;

		// object grid of Board class
        	Board grid;

		// boolean indicating end of game
		bool end_game;
	        

		// structure for reading player names and high scores
		struct Player
		{
			string curr_name;
			int score;
                };
		
	        // dynamic array to put all high scores and names in
		Player* high_scores;

		// number of lines in high score file
		int line_count;


	public:
		// Constructor for Game class
		Game();
		// Deconstructor for Game class
        	~Game();



		// Setters and Getters for all attributes

		// Parameters: character
		// Returns: nothing
		// Does: sets value of move attribute
		void set_move(char);
		
		// Parameters: string
		// Returns: nothing
		// Does: sets value of user_name attribute
		void set_user_name(string);

		// Parameters: integer
		// Returns: nothing
		// Does: sets value of current_score attribute
        	void set_current_score(int);

		// Parameters: boolean
	        // Returns: nothing
		// Does: sets value of end_game attribute
		void set_end_game(bool);

		// Parameters: line_count
		// Returns: nothing
		// Does: sets value of line_count attribute
		void set_line_count(int);


		// Parameters: none
		// Returns: value of move character (char w/a/s/d/h/q)
		// Does: gets value of move attribute		
		char get_move();

		// Parameters: none
		// Returns: user_name attribute
		// Does: gets value of user_name attribute
		string get_user_name();

		// Parameters: none
		// Returns: nothing
		// Does: sets value of current_score attribute
        	int get_current_score();

		// Paramters: none
		// Returns: nothing
		// Does: sets value of end_game attribute
		bool get_end_game();

		// Parameters: none
		// Returns: nothing
		// Does: sets value of line_count attribute
		int get_line_count();




		// parameters: none
		// returns: nothing
		// does: interprets user's move and sorts to appropriate 
		// function. This includes calling print high scores
		// function as well as quitting.
		void read_move();


		// parameters: none
		// uses grid attribute
		// returns: true or false
		// does: checks if game is over
        	bool check_game_over();


		// parameters: none
		// uses current score attribute
		// returns: nothing
        	// does: function called when game ends. function reads in
		// from highscores.txt and fills high_scores array
		//  with data from file.
		void high_score_read();
		
		// parameters: none
		// uses current score attribute
		// returns: nothing
		// does: sorts the current score and associated username 
	        // into the appropriate positions in high score list
		void high_score_sort();

		// parameters: none
		// returns: nothing
        	// does: reads in from the high scores file. Print first 
		// five scores and names associated with those scores. 
		// Called in game
        	void print_high_scores();

		// parameters: none
		// returns: nothing
		// does: reads in from high score file. Prints top high
		// score at the beginning of the game.
		string print_first_score();

		// parameters: none
		// returns: nothing
		// does: writes the high scores and corresonding arrays
		// from the high_scores struct to highscores.txt file
		void high_score_write();

		// parameters: none
		// returns: nothing
		// does: calls all the functions necessary to run game in 
                // correct order
		void run_game();

		// parameters: none
		// returns: nothing
		// does: calls appropriate movement function to shift board 
	     	void board_move();

};

#endif


