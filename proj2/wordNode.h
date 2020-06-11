/*
 *  Responsible for defining the struct that holds the information for every
 *  word read in.
 *
 *
 *  COMP 15 Proj 2 Gerp - It's Like grep But Something Is Off
 *
 *  wordNode.h
 *  Complete wordNode struct definition
 *  Modified By (UTLN): asahra01
 *
 */

#ifndef WORDNODE_H
#define WORDNODE_H

using namespace std;

// Struct holding all of the necessary information for a word read in from a 
// file
struct wordNode 
{
	string convertedWord;
	string originalWord;
	int lineNum;
	wordNode *next;
	int lineIndex;
	int pathIndex;
};

#endif
