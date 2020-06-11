/*
 *  Responsible for defining the parameters of the wordTable class as 
 *  well as categorizing all of the public and private members of the class.
 *
 *
 *  COMP 15 Proj 2 Gerp - It's Like grep But Something Is Off
 *
 *  wordTable.h
 *  Complete wordTable Class Header and Declaration
 *  Modified By (UTLN): asahra01
 *
 */

#ifndef WORDTABLE_H
#define WORDTABLE_H

#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <functional>
#include <vector>

#include "wordNode.h"


const double LOAD_FACTOR = 0.7;


class wordTable
{
	private:
		wordNode **linkedTable;

		static const int INITIAL_CAPACITY = 10;
		int currentSize;
		int tableCapacity;


		// Parameters: key (lower case equivalent of word, string)
		// Returns: hash value (size_t)
		// Generates a hash value for a given string using the std::hash 
		// function
		static size_t hashFunction(string);


		// Parameters: pointer to a word node, index to insert the node at
		// Returns: nothing
		// If the given index in the table has a value of NULL, the index 
		// points to the new node. If there is collision, the new node is 
		// inserted in the first spot. Calls expand function, if necessary.
		void insertWord(wordNode *, size_t);


		// Parameters: pointer to the current wordNode
		// Returns: whether a node was printed or not (bool)
		// Prints the information for a given node (line num, path, full line)
		bool printNode(wordNode *curr);


		// Parameters: pointer to the current wordNode and a reference to the 
		// vector containing all previously printed nodes (from the same path 
		// and line)
		// Returns: whether a node from the same path and line has been printed 
		// in this query (bool)
		// Checks whether a node form the same path and line has been printed 
		// during the current query
		bool checkPrevPrint(wordNode *, vector<wordNode *> & );

		// Parameters: pointer a word node, index in new table, pointer to new 
		// table
		// Returns: nothing
		// Inserts the nodes from the old table into the new table by 
		// reassigning the pointers.
		void expandHelper(wordNode *, size_t, wordNode **);

		// Parameters: all previous printed nodes from this query (reference to
		// vector of wordNode pointers), the original query input, the lower
		// case equivalent of the query input, the search type (@i or not) and 
		// the index of the hash table to look in
		// Returns: whether the node was found or not (bool)
		// Looks for a node matching the query specifications at a specific 
		// index in the hash table and only sends to print function if not 
		// previously printed
		bool findNode(vector<wordNode *> & v, string originalInput, 
							string input, bool ins, size_t index);



	public:

		// Default constructor
		// Allocates memory for hash table (dynamic array) of node pointers.
		// Initializes the initial capacity and set all values in table to NULL.
		wordTable();

		// Parameters: word from file (string), line number (int)
		// Returns: nothing
		// Creates a wordNode to store the information for a word in a file and 
		// inserts a pointer to that node in the table
		void makeNode(string, int);

		// Destructor
		~wordTable();

		// Parameters: none
		// Returns: nothing
		// increases capacity of hash table so that each chain has less nodes 
		// in it, thus increasing access and query time (closer to constant 
		// access time)
		void expand();


		// Parameters: none
		// Returns: nothing
		// Prints the information of every node in the hash table. Used for 
		// debugging.
		void print();


		// Parameters: search type: @i or not (bool), query input (string)
		// Returns: nothing
		// Hashes the lowercase conversion of the word and generates an index 
		// for the word. Passes the necessary search parameters to findNode(). 
		// If the node is not found, prints appropriate "not found" message.
		void searchTable(bool, string);

		// vector containing all lines that have been read in
		vector<string> allLines;

		// vector containing all paths of nonempty files that have been read in 
		// from
		vector<string> allPaths;

		// number of lines that have been read in
		int fullLineCount = 0;

		// numer of nonempty files that have been read in from
		int pathCount = 0;
};


#endif
