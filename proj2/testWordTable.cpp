/*
 *  Responsible for the testing of all of the members in the 
 *  wordTable class.
 *
 *
 *  COMP 15 Proj 2 Gerp - It's Like grep But Something Is Off
 *
 *  testWordTable.cpp
 *  Complete wordTable Class Test
 *  Modified By (UTLN): asahra01
 */

#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <functional>

using namespace std;

#include "wordTable.h"
#include "wordNode.h"

int main()
{
	wordTable table1;

	table1.makeNode("apple", 4, "/comp15/files/hw4", "hello apple");

	table1.makeNode("pear", 6, "/comp15/files/hw4", "taste pear");

	table1.makeNode("banana", 8, "/comp15/files/hw4", "eat banana");

	table1.makeNode("grape", 10, "/comp15/files/hw4", "grape yum");

	table1.makeNode("grape", 11, "/comp15/files/hw4", "grape soda");

	table1.makeNode("orange", 12, "/comp15/files/hw4", "orange juice");

	table1.makeNode("yellow", 15, "/comp15/files/hw4", "yellow fever");

	table1.makeNode("green", 63, "/comp15/files/hw4", "green lime");

	table1.makeNode("blue", 42, "/comp15/files/hw4", "blue ocean");

	table1.makeNode("purple", 88, "/comp15/files/hw4", "purple drank");

	table1.makeNode("silver", 15, "/comp15/files/hw4", "silver fox");

	table1.print();
}
