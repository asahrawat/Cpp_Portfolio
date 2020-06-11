/*
 *  Responsible for the implementation of all of the members in the 
 *  DatumStack class.
 *
 *
 *  COMP 15 Proj 1 CalcYouLater - Reverse Polish Notation Arithmetic
 *
 *  DatumStack.cpp
 *  Complete DatumStack Class Implementation
 *  Modified By (UTLN): asahra01
 *
 */


#include <string>
#include <stdexcept>
#include <iostream>
#include "Datum.h"
#include "DatumStack.h"

using namespace std;


// default constructor
DatumStack::DatumStack()
{
	front = NULL;
	length = 0;
}


// destructor
DatumStack::~DatumStack()
{
	while(front != NULL)
	{
		datumNode* temp = front;

		front = front->next;

		delete temp->data;		

		delete temp;

		length--;
	}

	length = 0;
}


// Parameters: array of Datums (Datum []) and length of array (int)
// Returns: nothing
// Turns an array of Datum into a Datum stack where the last Datum is
// at the top

DatumStack::DatumStack(Datum ray[], int len)
{
	datumNode *newNode = new datumNode;
	newNode->data = new Datum(ray[0]);

	newNode->next = NULL;

	front = newNode;
	datumNode *temp = newNode;

	for(int i = 1; i < len; i++)
	{
		newNode = new datumNode;
		newNode->data  = new Datum(ray[i]);

		front = newNode;

		newNode->next = temp;
		temp = newNode;
	}

	length = len;
}


// Parameters: none
// Returns: whether stack is empty or not (bool)
// Determines whether stack is empty of not

bool DatumStack::isEmpty()
{
	if(length == 0)
		return true;
	else
		return false;
}

// Parameters: none
// Returns: nothing
// Clears contents of the datum stack

void DatumStack::clear()
{

	while(front != NULL)
	{
		datumNode* temp = front;

		front = front->next;

		delete temp->data;

		delete temp;

		length--;
	}

	length = 0;
}

// Parameters: none
// Returns: nothing
// Finds the number of datum in the datum stack

int DatumStack::size()
{
	return length;
}



// Parameters: none
// Returns: nothing
// Finds top Datum in the first node of the stack and returns
// the Datum

Datum DatumStack::top()
{
	if(length == 0)
		throw runtime_error("empty_stack");

	return *(front->data);
}


// Parameters: none
// Returns: nothing
// Removes the first node from the stack

void DatumStack::pop()
{
	if(length == 0)
		throw runtime_error("empty_stack");

	datumNode *temp = front;

	front = front->next;

	delete temp->data;

	delete temp;

	length--;
}

// Parameters: new Datum (Datum)
// Returns: nothing
// Pushes new Datum to the top of the stack

void DatumStack::push(Datum elem)
{
	datumNode* newNode = new datumNode;

	newNode->data = new Datum(elem);

	newNode->next = front;

	front = newNode;

	length++;

	//print();
}


// Parameters: none.
// Returns: nothing
// Prints the contents of the stack. Used for debugging/testing

/*void DatumStack::print()
{
	datumNode *temp = front;


	while(temp != NULL)
	{
		cout << temp->data->toString() << endl;
		temp = temp->next;
	}

	cout << endl << endl;
}*/

