/*
 *  Implementation of directory tree traversal function
 *  
 *
 *
 *  COMP 15 Proj 2 Gerp - It's Like grep But Something Is Off 
 *
 *  FSTreeTraversal.cpp
 *  FSTreeTraversal function implementation
 *  Modified By (UTLN): asahra01
 *
 */


#include <iostream>
#include <cstdlib>
#include <string>

#include "FSTree.h"
#include "DirNode.h"

using namespace std;


// Parameters: pointer to highest directory (DirNode *)
// Returns: nothing
// Begins the path name for every subdirectory from the directory name. 
// Calls the treeTraverseHelper
void treeTraverser(DirNode *);


// Parameters: path to current directory (string), pointer to current 
// directory (DirNode *)
// Returns: nothing
// Recursively traverses through each subfolder, appending the subdirectory
// names along the way. Then appends the filenames for each files in the 
// current directory and prints the complete path for each file. 
void treeTraverserHelper(string, DirNode *);

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		cerr << "Usage:    treeTraversal Directory" << endl
			 << "	Please enter two arguments" << endl;
	}
	else
	{
		string highestDir = argv[1];

		// Make FSTree for directory provided
		FSTree * dirTree = new FSTree(highestDir);
		
		// Pass root of FSTree to start traversal
		DirNode * root = dirTree->getRoot();
		treeTraverser(root);

		delete dirTree;
	}
	return 0;
}





// Parameters: pointer to highest directory (DirNode *)
// Returns: nothing
// Begins the path name for every subdirectory from the directory name. 
// Calls the treeTraverseHelper
void treeTraverser(DirNode * root)
{
	string rootName = root->getName();
	treeTraverserHelper(rootName, root);
}


// Parameters: path to current directory (string), pointer to current 
// directory (DirNode *)
// Returns: nothing
// Recursively traverses through each subfolder, appending the subdirectory
// names along the way. Then appends the filenames for each files in the 
// current directory and prints the complete path for each file. 
void treeTraverserHelper(string currPath, DirNode * currDir)
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

			cout << currPath + "/" + fileName << endl;
		}
	}
	else
		cout << currPath << endl;
}

