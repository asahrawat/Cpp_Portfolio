/*
 *  Responsible for the implementation of gerp command line arguments
 *
 *
 *  COMP 15 Proj 2 Gerp - It's Like grep But Something Is Off
 *
 *  main.cpp
 *  
 *  Modified By (UTLN): asahra01
 *
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <string>

#include "wordNode.h"
#include "wordTable.h"
#include "FSTree.h"
#include "DirNode.h"
#include "gerpSearch.h"

using namespace std;


int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		cerr << "Usage:  gerp directory" << endl
			 << "            where:  directory is valid directory" << endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		string highestDir = argv[1];

		gerpSearch gerp1;

		gerp1.indexDirectory(highestDir);

		gerp1.processQuery();

	}
	return 0;
}
