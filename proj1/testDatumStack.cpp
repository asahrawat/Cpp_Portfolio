/*
 *
 *  Responsible for creating instances of the 
 *  DatumStack class and testing all of the functions on those instances
 *
 *  COMP 15 Proj 1 CalcYouLater - Reverse Polish Notation Arithmetic
 *
 *  testDatumStack.cpp
 *  Testing File for your sequence DatumStack class
 *
 *  Written by: Amun Sahrawat
 *        UTLN: asahra01
 */

#include <iostream>
#include "DatumStack.h"
#include "Datum.h"

using namespace std;




int main()
{


	Datum datum1(60);
	Datum datum2(79);
	Datum datum3(44);


	Datum datumArray [3] = {datum1, datum2, datum3};

	// Create three different instances of CharLinkedList class
	// These were not the only lists used for testing.
	DatumStack stack1;

	DatumStack stack2(datumArray, 3);

	stack1.push(datum1);

	stack1.print();

	stack1.push(datum2);

	stack1.print();

	stack1.push(datum3);

	stack1.print();

	stack1.pop();

	stack1.print();

	stack1.pop();

	stack1.print();

	stack1.pop();	

	stack1.print();


	// print function test
	// push array of datums to stack and then print them individually
	stack2.print();

	stack2.push(datum1);

	stack2.print();

	stack2.push(datum2);

	stack2.print();

	stack2.push(datum3);

	stack2.print();

	stack2.pop();

	stack2.print();

	stack2.pop();

	stack2.print();

	stack2.pop();	

	stack2.print();

	stack2.pop();

	stack2.print();

	stack2.pop();	

	stack2.print();



	// Empty function test
	// Push a datum array to a stack, print out the top value, then clear
	// the stack and make sure that isEmpty returns true (or 1)
	DatumStack stack3(datumArray, 3);

	stack3.print();

	cout << stack3.top().toString();

	stack3.clear();

	stack3.print();

	cout << stack3.isEmpty() << endl;
	
}


