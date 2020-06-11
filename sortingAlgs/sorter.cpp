/*
 *  Responsible for handling the implementation of all of the command line 
 *  arguments for the program. This includes all input and output possibilites
 *
 *
 *  Homework 5: All Sorts of Sorta Nice Sortin' Algorithms
 *
 *  sorter.cpp
 *  Complete main for program
 *  Modified By (UTLN): asahra01
 *
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string>
#include "sortAlgs.h"

using namespace std;

void usageAbort();
void readIn(vector<int> & );
void readFromFile(string, vector<int> & ); 
void sortVector(string, vector<int> &);
void printSortedFile(string, vector<int> &, string);
void printSortedSave(string, vector<int> &);
string convertSort(string);
void printStandardOutput(vector<int> &);

// Parameters: command line arguments
// Returns: 1 or 0 (depending on error or not)
// Responsible for the implementation of command line arguments and calling
// correct functions at appropriate times
int main(int argc, char *argv[])
{    
	string sortType = argv[1];
	string outputType = argv[2];

	if((argc == 3 || argc == 4) && (sortType == "-s1" || sortType == "-s2" || 
		sortType == "-s3") && (outputType == "--save" || 
		outputType == "--print")) 
	{		
		vector<int> toSort;
		if(argc == 4)
			readFromFile(argv[3], toSort);
		else
			readIn(toSort);

		sortVector(sortType, toSort);
		if(outputType == "--save")
			if(argc == 4)
				printSortedFile(sortType, toSort, argv[3]);
			else
				printSortedSave(sortType, toSort);
		else
			printStandardOutput(toSort);
	}
	else {
		usageAbort();
		exit(1);	
	}
    return 0;
}



// Parameters: sort type (string)
// Returns: modified sort type (string)
// Converts the -s'n' sort type to just 'n'
string convertSort(string sortType)
{
	if(sortType == "-s1")
		return "1";
	else if (sortType == "-s2")
		return "2";
	else
		return "3";
}


// Paramters: sort type (string), sorted vector (vector reference) and name of
// file read in from (string)
// Returns: none
// Prints the sorted array to a file, if values were read in from a file
void printSortedFile(string sort, vector<int> &v1, string readFile)
{
	string newSort = convertSort(sort);
	int length = (int) v1.size();
	string stringLength;
	stringstream ss;
	ss << length;
	stringLength = ss.str();

	string filename = readFile + "_" + newSort + "_" + stringLength + 
																"_sorted.txt";

	ofstream outfile;
	outfile.open (filename.c_str());

	for(int i = 0; i < (int) v1.size(); i++)
	{
		outfile << v1[i] << endl;
	}

	outfile.close();
}

// Parameters: sort type (string), sorted vector (vector reference)
// Returns: none
// Prints the sorted array to a file, if values were read in from cin
void printSortedSave(string sort, vector<int> &vec1)
{
	string newSort = convertSort(sort);
	int length = (int) vec1.size();
	string stringLength;
	stringstream ss;
	ss << length;
	stringLength = ss.str();

	string filename = "cin_" + newSort + "_" + stringLength + "_sorted.txt";

	ofstream outfile;
	outfile.open (filename.c_str());

	for(int i = 0; i < (int) vec1.size(); i++)
	{
		outfile << vec1[i] << endl;
	}

	outfile.close();
}


// Parameters: sorted vector (vector reference)
// Returns: none
// Prints the sorted array to cout
void printStandardOutput(vector<int> &vec1)
{
	for(int i = 0; i < (int) vec1.size(); i++)
	{
		cout << vec1[i] << endl;
	}
}


// Parameters: sort type (string), unsorted vector (vector reference)
// Returns: none
// Calls the appropriate sorting algorithm
void sortVector(string sortingAlg, vector<int> &vec1)
{
	if(sortingAlg == "-s1")
		insertionSort(vec1);

	else if(sortingAlg == "-s2")
		quickSort(vec1);

	else
		shellSort(vec1);
}

// Parameters: filename (string), empty vector (vector reference)
// Returns: none
// Reads in input elements from file into the vector
void readFromFile(string filename, vector<int> &v)
{
    ifstream   infile;
    infile.open(filename.c_str());
    int num;
    
    if (not infile.is_open()) 
            cerr << "Unable to open " << filename << endl;
    else
    {
    	for(infile >> num; not infile.eof(); infile >> num)
    	{
    		v.push_back(num);
    	}

    }

    infile.close();
}


// Parameters: empty vector (vector reference)
// Returns: none
// Reads in input elements from cin into the vector
void readIn(vector<int> &v)
{
	int input;

	while (	cin >> input)
	{
		v.push_back(input);
	}
}



// Parameters: none
// Returns: none
// Called when input parameters are incorrect
void usageAbort()
{
        cerr << "Usage:  sorter sortAlg outputMode [fileName]" << endl
             << "            where:  sortAlg is -s1, -s2, or -s3" << endl
             << "            and     outputMode is --print or --save" << endl;

        exit(1);
}
