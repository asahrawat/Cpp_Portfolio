/*
 *  Responsible for the implementation of all of the members in the 
 *  gerpSearch class.
 *
 *
 *  COMP 15 Proj 2 Gerp - It's Like grep But Something Is Off
 *
 *  gerpSearch.cpp
 *  Complete gerpSearch Class Implementation
 *  Modified By (UTLN): asahra01
 *
 */

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
#include "gerpSearch.h"

using namespace std;


// Default constructor
// initializes searchOver variable to false
gerpSearch::gerpSearch()
{
	searchOver = false;
}

// Destructor
gerpSearch::~gerpSearch()
{

}


// Parameters: pointer to highest directory (DirNode *)
// Returns: nothing
// Begins the path name for every subdirectory from the directory name. 
// Calls the treeTraverseHelper
void gerpSearch::treeTraverser(DirNode * root)
{
	string rootName = root->getName();
	treeTraverserHelper(rootName, root);
}




// Parameters: path to current directory (string), pointer to current 
// directory (DirNode *)
// Returns: nothing
// Recursively traverses through each subfolder, appending the subdirectory
// names along the way. Then appends the filenames for each files in the 
// current directory and prints the complete path for each file. Calls 
// readFromFile() for every file in the tree.
void gerpSearch::treeTraverserHelper(string currPath, DirNode * currDir)
{
	if(currDir->hasSubDir() == true)
	{
		for(int i = 0; i < currDir->numSubDirs(); i++)
		{
			string subDirName = currDir->getSubDir(i)->getName();
			string subDirNamePath = currPath + "/" + subDirName;

			treeTraverserHelper(subDirNamePath, currDir->getSubDir(i));
		}
	}

	if(currDir->hasFiles() == true)
	{
		for(int i = 0; i < currDir->numFiles(); i++)
		{
			string fileName = currDir->getFile(i);

			string fullPath = currPath + "/" + fileName;
			readFromFile(fullPath);
		}
	}
}


// Parameters: highest directory (string, provided by client)
// Returns: nothing
// Creates an FSTree from the highest directory. Deletes the tree after the
// indexing has completed
void gerpSearch::indexDirectory(string highestDir)
{
	// Make FSTree for directory provided
	FSTree * dirTree = new FSTree(highestDir);
		
	// Pass root of FSTree to start traversal
	DirNode * root = dirTree->getRoot();
	treeTraverser(root);

	delete dirTree;
}

// Parameters: path to file (string)
// Returns: nothing
// Reads in the file at the given path line by line, storing each line in a 
// vector. Then reads each line word by word, stripping all non alpha-numerical
// characters off of each end and sends each word to the processWord function.
void gerpSearch::readFromFile(string path)
{
	ifstream infile;
	infile.open(path.c_str());

	if (not infile.is_open())
		cerr << "Unable to open " << path << endl;
	else {
		hashTable.allPaths.push_back(path);
		string fullLine;
		int line_count = 0;
		while(not infile.eof()) {
			getline(infile, fullLine);
			line_count++;
			stringstream ss(fullLine);

			vector<string> alreadyInserted;
			string sepWord;
			while(ss >> sepWord)
				processWord(sepWord, alreadyInserted, line_count);

			//verify something's actually going to be read in from the line
			if(stripNonAlphaNum(fullLine) != "") {
				hashTable.allLines.push_back(fullLine);
				hashTable.fullLineCount++;
			}
		}
	}
	infile.close();
	hashTable.pathCount++;
}


// Parameters: word (string), reference to vector containing all previously
// inserted words from a given line, the line number (int)
// Returns: nothing
// Checks if the exact same word from the same line of the same file has been 
// inserted before. If not, then calls makeNode for that word.
void gerpSearch::processWord(string sepWord, vector<string> & v, int line_count)
{
	sepWord = stripNonAlphaNum(sepWord);
	bool prevInsert = checkPrevInsert(sepWord, v);
	if(prevInsert == false and sepWord != "")
	{
		hashTable.makeNode(sepWord, line_count);
		v.push_back(sepWord);
	}
}



// Parameters: word to be inserted (string), reference to vector containing all
// previously inserted words from a given line
// Returns: whether the same word has been isnerted before (boolean)
// Checks if the given word already appears in the vector of prevoiusly
// inserted words for that line.
bool gerpSearch::checkPrevInsert(string toInsert, vector<string> & v)
{
	if(v.empty() == true)
		return false;

	for(size_t i = 0; i < v.size(); i++)
	{
		if(toInsert == v[i])
		{
			return true;
		}
	}
	return false;
}




// Parameters: original string (string)
// Returns: stripped string (string)
// strips all non alpha-numerical characters off of each end of the 
// original string
string gerpSearch::stripNonAlphaNum(string oldString)
{
	int start = 0;
	int end = oldString.length() - 1;
	string newString = "";

	while(start <= end && isalnum(oldString[start]) == false)
	{
		start++;
	}

	if(start > end)
	{
		return newString;
	}

	else
	{
		while(isalnum(oldString[end]) == false)
			end--;
		for(int i = start; i <= end; i++)
			newString+=oldString[i];

		return newString;
	}
}


// Parameters: none
// Returns: none
// Processes user's query specifications (word and case insensitive or not.
// Strips off all non alphanumeric chars from either end of input and
// sends input to searchTable() function to be processed.
void gerpSearch::processQuery()
{
	string input;
	while(searchOver == false) {
		cout << "Query? ";
		cin >> input;

		if(input == "@i" || input == "@insensitive") {
			cin >> input;
			input = stripNonAlphaNum(input);
			if(input == "")
				cout << "\"\" Not Found.\n";
			else
				hashTable.searchTable(true, input);
		}
		else if(input == "@q" || input == "@quit")
			searchOver = true;

		else if(cin.eof() == true)
			searchOver = true;	
		else
		{
			input = stripNonAlphaNum(input);
			if(input == "")
				cout << "\"\" Not Found. Try with @insensitive or @i.\n";
			else
				hashTable.searchTable(false, input);
		}
	}
	cout << endl << "Goodbye! Thank you and have a nice day.\n";
}





