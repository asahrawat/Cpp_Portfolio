/*
 *  Responsible for defining the parameters of the RPNCalc class as 
 *  well as categorizing all of the public and private members of the class.
 *
 *
 *  COMP 15 Proj 1 CalcYouLater - Reverse Polish Notation Arithmetic
 *
 *  RPNCalc.h
 *  Complete RPNCalc Class Header and Declaration
 *  Modified By (UTLN): asahra01
 *           On       : 10/6/17
 *
 */

#ifndef RPNCALC_H
#define RPNCALC_H

#include <string>
#include <stdexcept>
#include <sstream>
#include <fstream>
#include <cstdio>
#include <fstream>
#include "Datum.h"
#include "DatumStack.h"

using namespace std;

class RPNCalc {

	private:

		// Declaration and initialization of stack
		DatumStack stack1;

		// Declaration of bool that determines if calculator use if over
		bool calcOver;

		// parameters: a string and an int*
		// returns: boolean
		// Verifies whether a given string is an int or not (can be used to 
		// convert string to int)
		bool got_int(string s, int *resultp);

		// Parameters: none
		// Returns: nothing
		// pushes the boolean inverse of the top element on the stack
		void notHelper();

		// Parameters: none
		// Returns: nothing
		// prints the element on top of the stack to cout
		void printHelper();

		// Parameters: none
		// Returns: nothing
		// duplicates the top element on the stack and pushes it (copy on top)
		void dupHelper();

		// Parameters: none
		// Returns: nothing
		// swaps the top two elements on the stack
		void swapHelper();


		// Parameters: current input (string)
		// Returns: nothing
		// Performs an elementary operation two int Datums on top of the stack
		void elementaryOps(string);


		// Parameters: current input (string), both datums (ints)
		// Returns: nothing
		// Divides two datums and either pushes the quotient or the remaineder 
		// onto the stack (depending on which one is required)
		void divisionHelper(string, int, int);


		// Parameters: current input (string)
		// Returns: nothing
		// Sorts the input based to the appropriate processing function
		void comparisonOps(string);


		// Parameters: current input (string)
		// Returns: nothing
		// Sorts input to relevant processing function
		void processInput(string);


		// Parameters: none
		// Returns: nothing
		// determines if the top two datums on the stack are equal or not
		void equalityHelper();


		// Parameters:  top two datums on stack (ints), current input (string)
		// Returns: nothing
		// performs a comparison operation on the top two integers in the 
		// stack
		void comparisonOpsCheck(int, int, string);


		// Parameters: current istream (istream&)
		// Returns: nothing
		// Opens target file and passes ifstream to readAndProcess()
		void fileHelper(istream&);

		// Parameters: current istream (istream&)
		// Returns: nothing
		// pushes parsed code block onto the stack
		void codeBlockHelper(istream&);


		// Parameters: none
		// Returns: nothing
		// executes a code block on top of the stack
		void execHelper();


		// Parameters: none
		// Returns: nothing
		// Checks if the 'if' function can be applied given the stack's 
		// current state
		void ifChecker();


		// Parameters: true case (string), false case (string), 
		// and condition (bool)
		// Returns: nothing
		// Performs 'if' function on top three elements of stack (as specified
		// by project spec)
		void ifHelper(string, string, bool);


		// Parameters: reference to istream (istream &)
		// Returns: nothing
		// Reads and processes any stream it is given (reads from string, 
		// file, or cin). Pushes all numbers onto the stack
		void readAndProcess(istream&);


		// Parameters: current istream (istream&)
		// Returns: parsed code block (string)
		// parses a given code block (removes outer-most curly braces)
		string parseCodeBlock(istream &input);


	public:

		// default constructor
		RPNCalc();

		// destructor
		~RPNCalc();

		// Parameters: none
		// Returns: nothing
		// Runs the RPN Calculator
		void run();



};


#endif
