/*
 *  Responsible for the implementation of all of the members in the 
 *  wordTable class.
 *
 *
 *  COMP 15 Proj 2 Gerp - It's Like grep But Something Is Off
 *
 *  wordTable.cpp
 *  Complete wordTable Class Implementation
 *  Modified By (UTLN): asahra01
 *
 */

#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <functional>
#include <vector>

#include "wordTable.h"
#include "wordNode.h"

using namespace std;

// Default constructor
// Allocates memory for hash table (dynamic array) of node pointers.
// Initializes the initial capacity and set all values in table to NULL.
wordTable::wordTable()
{
	tableCapacity = INITIAL_CAPACITY;
	currentSize = 0;

	linkedTable = new wordNode *[tableCapacity];

	for(int i = 0; i < tableCapacity; i++)
		linkedTable[i] = NULL;
}

// Destructor
wordTable::~wordTable()
{
	for(int i = 0; i < tableCapacity; i++)
	{
		wordNode *tracker = linkedTable[i];
		wordNode *toDelete = tracker;

		while(tracker != NULL)
		{
			tracker = tracker->next;
			delete toDelete;
			toDelete = tracker;
		}
	}
	delete [] linkedTable;
}


// Parameters: none
// Returns: nothing
// increases capacity of hash table so that each chain has less nodes in it,
// thus increasing access and query time (closer to constant access time)
void wordTable::expand()
{
	wordNode **newTable = new wordNode *[2 + tableCapacity * 2];

	for(int i = 0; i < (2 + tableCapacity * 2); i++)
		newTable[i] = NULL;

	for(int i = 0; i < tableCapacity; i++)
	{
		wordNode *tracker = linkedTable[i];
		wordNode *toHash = tracker;

		while(tracker != NULL)
		{
			tracker = tracker->next;

			toHash->next = NULL;
			size_t newHVal = hashFunction(toHash->convertedWord);
			size_t newIndex = newHVal % (2 + tableCapacity * 2);
			expandHelper(toHash, newIndex, newTable);

			toHash = tracker;
		}
	}
	delete [] linkedTable;

	linkedTable = newTable;

	tableCapacity = 2 + tableCapacity * 2;
}


// Parameters: pointer a word node, index in new table, pointer to new table
// Returns: nothing
// Inserts the nodes from the old table into the new table by reassigning the
// pointers.
void wordTable::expandHelper(wordNode *node, size_t index, wordNode **table)
{
	if(table[index] == NULL)
		table[index] = node;
	else
	{
		node->next = table[index];
		table[index] = node;
	}
}


// Parameters: key (lower case equivalent of word, string)
// Returns: hash value (size_t)
// Generates a hash value for a given string using the std::hash function
size_t wordTable::hashFunction(string key)
{
	return std::hash<string>{}(key);
}


// Parameters: pointer to a word node, index to insert the node at
// Returns: nothing
// If the given index in the table has a value of NULL, the index points to the
// new node. If there is collision, the new node is inserted in the first spot.
// Calls expand function, if necessary.
void wordTable::insertWord(wordNode *newNode, size_t index)
{
	if(currentSize / (double)tableCapacity >= LOAD_FACTOR)
		expand();

	if(linkedTable[index] == NULL)
	{
		linkedTable[index] = newNode;
	}
	else
	{
		newNode->next = linkedTable[index];
		linkedTable[index] = newNode;
	}
	currentSize++;
}

// Parameters: word from file (string), line number (int)
// Returns: nothing
// Creates a wordNode to store the information for a word in a file and inserts
// a pointer to that node in the table
void wordTable::makeNode(string word, int line_num)
{
	wordNode* newNode = new wordNode;
	newNode->next = NULL;
	newNode->originalWord = word;
	newNode->lineNum = line_num;

	newNode->lineIndex = fullLineCount;
	newNode->pathIndex = pathCount;

	for(size_t i = 0; i < word.length(); i++)
	{
		word[i] = tolower(word[i]);
	}

	newNode->convertedWord = word;

	size_t hVal = hashFunction(word);
	size_t index = hVal % tableCapacity;

	insertWord(newNode, index);
}


// Parameters: none
// Returns: nothing
// Prints the information of every node in the hash table. Used for debugging.
void wordTable::print()
{
	for(int i = 0; i < tableCapacity; i++)
	{
		wordNode *temp = linkedTable[i];
		while(temp != NULL)
		{
			cout << "Original Word: " << temp->originalWord << endl;
			cout << "Converted Word: " << temp->convertedWord << endl;
			cout << "Line Number: " << temp->lineNum << endl;
			cout << "Path of word: " << allPaths[temp->pathIndex] << endl;
			cout << "Full line for word: " << allLines[temp->lineIndex] << endl;

			temp = temp->next;
		}
	}
}

// Parameters: search type: @i or not (bool), query input (string)
// Returns: nothing
// Hashes the lowercase conversion of the word and generates an index for the
// word. Passes the necessary search parameters to findNode(). if the node
// is not found, prints appropriate "not found" message.
void wordTable::searchTable(bool insensitive, string input)
{
	bool found;

	string originalInput = input;
	vector<wordNode *> alreadyPrinted;

	for(size_t i = 0; i < input.length(); i++)
		input[i] = tolower(input[i]);

	size_t hVal = hashFunction(input);
	size_t index = hVal % tableCapacity;

	found = findNode(alreadyPrinted, originalInput, input, insensitive, index);

	if(found == false && insensitive == false)
		cout << originalInput << " Not Found. Try with @insensitive or @i.\n";
	else if(found == false && insensitive == true)
		cout << originalInput << " Not Found.\n";
}


// Parameters: all previous printed nodes from this query (reference to vector 
// of wordNode pointers), the original query input, the lower case equivalent
// of the query input, the search type (@i or not) and the index of the hash
// table to look in
// Returns: whether the node was found or not (bool)
// Looks for a node matching the query specifications at a specific index
// in the hash table and only sends to print function if not previously
// printed
bool wordTable::findNode(vector<wordNode *> & v, string originalInput, 
										string input, bool ins, size_t index)
{
	bool found = false;
	wordNode *temp = linkedTable[index];

	if(ins == true) {
		while(temp != NULL) {
			if(temp->convertedWord == input)
			{
				bool prevPrint = checkPrevPrint(temp, v);
				if(prevPrint == false)
				{
					found = printNode(temp);
					v.push_back(temp);
				}
			}
			temp = temp->next;
		}
	}
	else {
		while(temp != NULL) {
			if(temp->originalWord == originalInput)
				found = printNode(temp);

			temp = temp->next;
		}
	}
	return found;
}

// Parameters: pointer to the current wordNode and a reference to the vector
// containing all previously printed nodes (from the same path and line)
// Returns: whether a node from the same path and line has been printed 
// in this query (bool)
// Checks whether a node form the same path and line has been printed during 
// the current query
bool wordTable::checkPrevPrint(wordNode *curr, vector<wordNode *> & v)
{
	if(v.empty() == true)
		return false;

	for(size_t i = 0; i < v.size(); i++)
	{
		if(curr->lineNum == v[i]->lineNum && 
					allPaths[curr->pathIndex] == allPaths[v[i]->pathIndex])
		{
			return true;
		}
	}
	return false;
}


// Parameters: pointer to the current wordNode
// Returns: whether a node was printed or not (bool)
// Prints the information for a given node (line num, path, full line)
bool wordTable::printNode(wordNode *curr)
{
	cout << allPaths[curr->pathIndex] << ":" << curr->lineNum << ": ";
	cout << allLines[curr->lineIndex] << endl;
	return true;
}

