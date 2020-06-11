/*
 *  Responsible for the implementation of RPNCalc command line arguments
 *
 *
 *  COMP 15 Proj 1 CalcYouLater - Reverse Polish Notation Arithmetic
 *
 *  main.cpp
 *  
 *  Modified By (UTLN): asahra01
 *           On       : 10/12/17
 *
 */


#include <string>
#include <stdexcept>
#include <iostream>
#include <cstdio>
#include "Datum.h"
#include "DatumStack.h"
#include "RPNCalc.h"

using namespace std;


int main()
{
	RPNCalc calc1;

	calc1.run();

	return 0;
}

/*int main()
{
  //test size on stack with size 6 - should print 1
  Datum data[] = { Datum(8),Datum("hello"),Datum(5),Datum("{ 4 5 + }") };
  DatumStack stack(data, 4);
  std::cout << (stack.size()==4) << std::endl;
  
  //test on empty stack - should print 1
  DatumStack emptystack;
  std::cout << (emptystack.size()==0) << std::endl;
  
  return 0;
} */

