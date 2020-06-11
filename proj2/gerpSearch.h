/*
 *  Responsible for defining the parameters of the gerpSearch class as 
 *  well as categorizing all of the public and private members of the class.
 *
 *
 *  COMP 15 Proj 2 Gerp - It's Like grep But Something Is Off
 *
 *  gerpSearch.h
 *  Complete gerpSearch Class Header and Declaration
 *  Modified By (UTLN): asahra01
 *           On       : 11/27/17
 *
 */


#ifndef GERPSEARCH_H
#define GERPSEARCH_H


#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <string>
#include <vector>

#include "wordNode.h"
#include "wordTable.h"
#include "FSTree.h"
#include "DirNode.h"

using namespace std;


class gerpSearch
{
	private:
		// instantiate object of wordTable type (hash table)
		wordTable hashTable;
		// declare boolean determining whether search is over or not
		bool searchOver;

		// Parameters: pointer to highest directory (DirNode *)
		// Returns: nothing
		// Begins the path name for every subdirectory from the directory name. 
		// Calls the treeTraverseHelper
		void treeTraverser(DirNode *);



		// Parameters: path to current directory (string), pointer to current 
		// directory (DirNode *)
		// Returns: nothing
		// Recursively traverses through each subfolder, appending the 
		// subdirectory names along the way. Then appends the filenames for 
		// each files in the current directory and prints the complete path for 
		// each file. Calls readFromFile() for every file in the tree.
		void treeTraverserHelper(string, DirNode *);


		// Parameters: path to file (string)
		// Returns: nothing
		// Reads in the file at the given path line by line, storing each line 
		// in a vector. Then reads each line word by word, stripping all non 
		// alpha-numerical characters off of each end and sends each word to 
		// the processWord function.
		void readFromFile(string);



		// Parameters: original string (string)
		// Returns: stripped string (string)
		// strips all non alpha-numerical characters off of each end of the 
		// original string
		string stripNonAlphaNum(string oldString);


		// Parameters: word to be inserted (string), reference to vector 
		// containing all previously inserted words from a given line
		// Returns: whether the same word has been isnerted before (boolean)
		// Checks if the given word already appears in the vector of prevoiusly
		// inserted words for that line.
		bool checkPrevInsert(string, vector<string> &);

		// Parameters: word (string), reference to vector containing all 
		// previously inserted words from a given line, the line number (int)
		// Returns: nothing
		// Checks if the exact same word from the same line of the same file 
		// has been inserted before. If not, then calls makeNode for that word.
		void processWord(string, vector<string> &, int);


	public:

		// Default constructor
		// initializes searchOver variable to false
		gerpSearch();
		
		// Destructor
		~gerpSearch();

		// Parameters: highest directory (string, provided by client)
		// Returns: nothing
		// Creates an FSTree from the highest directory. Deletes the tree after
		// the indexing has completed
		void indexDirectory(string);

		// Parameters: none
		// Returns: none
		// Processes user's query specifications (word and case insensitive or 
		// not. Strips off all non alpha-numerical chars from either end of 
		// input and sends input to searchTable() function to be processed.
		void processQuery();


};

#endif