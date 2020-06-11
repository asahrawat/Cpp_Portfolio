 /*
 *  Implementation of the stripNonAlphaNum function, used to remove all 
 *  non alphanumerical characters from either end of a given string
 *  
 *
 *
 *  COMP 15 Proj 2 Gerp - It's Like grep But Something Is Off 
 *
 *  stringProcessing.cpp
 *  stringProcessing function implementation
 *  Modified By (UTLN): asahra01
 *
 */

#include <iostream>
#include <cstdlib>
#include <string>

#include "stringProcessing.h"

using namespace std;


// Parameters: original string (string)
// Returns: stripped string (string)
// strips all non alpha-numerical characters off of each end of the 
// original string
string stripNonAlphaNum(string oldString)
{
	int start = 0;
	int end = oldString.length() - 1;
	string newString = "";

	while(isalnum(oldString[start]) == false)
		start++;

	if(start == end)
		return newString;

	else
	{
		while(isalnum(oldString[end]) == false)
			end--;
		for(int i = start; i <= end; i++)
			newString+=oldString[i];

		return newString;
	}
}
