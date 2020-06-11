/*
 *  Responsible for defining the parameters of the DatumStack class as 
 *  well as categorizing all of the public and private members of the class.
 *
 *
 *  COMP 15 Proj 1 CalcYouLater - Reverse Polish Notation Arithmetic
 *
 *  DatumStack.h
 *  Complete DatumStack Class Header and Declaration
 *  Modified By (UTLN): asahra01
 *           On       : 10/1/17
 *
 */

#ifndef DATUMSTACK_H
#define DATUMSTACK_H

#include <string>
#include <stdexcept>
#include "Datum.h"


class DatumStack {
	
	private:

		//number nodes in linked list
		int length;

		struct datumNode 
		{
			// pointer to a Datum
			Datum* data;
			datumNode* next;
    	};

    	
    	datumNode *front;

    	


	public: 
		// default constructor
		DatumStack();

		// Parameters: array of Datums (Datum []) and length of array (int)
		// Returns: nothing
		// Turns an array of Datum into a Datum stack where the last Datum is
		// at the top
		DatumStack(Datum [], int);

		// destructor
		~DatumStack();


		// Parameters: none
		// Returns: whether stack is empty or not (bool)
		// Determines whether stack is empty of not
		bool isEmpty();


		// Parameters: none
		// Returns: nothing
		// Clears contents of the datum stack
		void clear();


		// Parameters: none
		// Returns: nothing
		// Finds the number of datum in the datum stack
		int size();


		// Parameters: none
		// Returns: nothing
		// Finds top Datum in the first node of the stack and returns
		// the Datum
		Datum top();


		// Parameters: none
		// Returns: nothing
		// Removes the first node from the stack
		void pop();


		// Parameters: new Datum (Datum)
		// Returns: nothing
		// Pushes new Datum to the top of the stack
		void push(Datum);


		// Parameters: none.
		// Returns: nothing
		// Prints the contents of the stack. Used for debugging/testing
		//void print();

};

#endif

