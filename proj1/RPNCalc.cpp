/*
 *  Responsible for the implementation of all of the members in the 
 *  RPNCalc class.
 *
 *
 *  COMP 15 Proj 1 CalcYouLater - Reverse Polish Notation Arithmetic
 *
 *  RPNCalc.cpp
 *  Complete RPNCalc Class Implementation
 *  Modified By (UTLN): asahra01
 *           On       : 10/6/17
 *
 */


#include <string>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <fstream>
#include "Datum.h"
#include "DatumStack.h"
#include "RPNCalc.h"

using namespace std;


// Default Constructor
// Initializes the calcOver attritbute
RPNCalc::RPNCalc()
{
	calcOver = false;
}


// Destructor
RPNCalc::~RPNCalc()
{
	stack1.clear();
}



// Parameters: none
// Returns: nothing
// Runs the RPN Calculator
void RPNCalc::run()
{
	readAndProcess(cin);
	//cout << "Thank you for using CalcYouLater\n";
}



// Parameters: reference to istream (istream &)
// Returns: nothing
// Reads and processes any stream it is given (reads from string, file, or cin)
// Pushes all numbers onto the stack
void RPNCalc::readAndProcess(istream& stream)
{
	string input;
	int convertedInt;
	while(stream >> input && calcOver == false)
	{
		if(got_int(input, &convertedInt))
			stack1.push(Datum(convertedInt));
		else if (input == "quit")
			calcOver = true;
		else if(input == "#t")
			stack1.push(Datum(true));
		else if(input == "#f")
			stack1.push(Datum(false));
		else if(input == "{")
			codeBlockHelper(stream);
		else if(input == "file")
			fileHelper(stream);
		else if(input == "clear")
			stack1.clear();
		else if(input != "not" && input != "print" && input != "clear" && 
			input != "drop" && input != "dup" && input != "if" && 
			input != "{" && input != "swap" && input != "+" && 
			input != "-" && input != "*" && input != "/" && input != "mod" && 
			input != "<" && input != ">" && input != "<=" && input != ">=" &&
			input != "==" && input != "exec")
			cerr << input << ": unimplemented\n";
		else 
			processInput(input);
	}
}



// Parameters: current input (string)
// Returns: nothing
// Sorts input to relevant processing function
void RPNCalc::processInput(string input)
{
	if(stack1.isEmpty() == true)
		cerr << "Error: empty_stack\n";

	else if(input == "not")
		notHelper();
	else if(input == "print")
		printHelper();
	else if(input == "drop")
		stack1.pop();
	else if(input == "dup")
		dupHelper();
	else if(input == "exec")
		execHelper();
	else if(input == "if")
		ifChecker();
	else if(input == "swap")
		swapHelper();

	else if(input == "+" || input == "-" || input == "*" || input == "/" || 
														input == "mod")
		elementaryOps(input);
	else if(input == "<" || input == ">" || input == "<=" || input == ">=" || 
														input == "==")
		comparisonOps(input);
}



// parameters: a string and an int*
// returns: boolean
// Verifies whether a given string is an int or not (can be used to 
// convert string to int)
bool RPNCalc::got_int(string s, int *resultp)
{
    return sscanf(s.c_str(), "%d", resultp) == 1;
}



// Parameters: none
// Returns: nothing
// pushes the boolean inverse of the top element on the stack
void RPNCalc::notHelper()
{
	if(stack1.top().isBool() == false)
		cerr << "Error: datum_not_bool\n";
	else
	{
		bool inverse;

		inverse = !(stack1.top().getBool());

		stack1.pop();

		stack1.push(Datum(inverse));
	}
}


// Parameters: none
// Returns: nothing
// prints the element on top of the stack to cout
void RPNCalc::printHelper()
{

	cout << stack1.top().toString() << endl;

}



// Parameters: none
// Returns: nothing
// duplicates the top element on the stack and pushes it (copy on top)
void RPNCalc::dupHelper()
{

	Datum topDatum = stack1.top();

	stack1.push(topDatum);

}


// Parameters: none
// Returns: nothing
// swaps the top two elements on the stack
void RPNCalc::swapHelper()
{

	Datum topDatum = stack1.top();

	stack1.pop();

	Datum secondDatum = stack1.top();

	stack1.pop();

	stack1.push(topDatum);

	stack1.push(secondDatum);


}




// Parameters: current input (string)
// Returns: nothing
// Performs an elementary operation two int Datums on top of the stack
void RPNCalc::elementaryOps(string input)
{
	if(stack1.top().isInt() == false)
		cerr << "Error: datum_not_int\n";
	else
	{
		int firstDatum = stack1.top().getInt();
		stack1.pop();
	
		if (stack1.isEmpty() == true)
			cerr << "Error: empty_stack\n";
		else if (stack1.top().isInt() == false)
			cerr << "Error: datum_not_int\n";
		else
		{
			int secondDatum = stack1.top().getInt();
			stack1.pop();

			if(input == "+")
				stack1.push(Datum(secondDatum + firstDatum));
			else if(input == "-")
				stack1.push(Datum(secondDatum - firstDatum));
			else if(input == "*")
				stack1.push(Datum(secondDatum * firstDatum));
			
			else if(input == "/" || input == "mod")
				divisionHelper(input, firstDatum, secondDatum);
		}
	}
}



// Parameters: current input (string), both datums (ints)
// Returns: nothing
// Divides two datums and either pushes the quotient or the remaineder onto
// the stack (depending on which one is required)
void RPNCalc::divisionHelper(string input, int firstDatum, int secondDatum)
{
	if(input == "/")
	{	
		if(firstDatum == 0)
			cerr << "Error: division by 0\n";
		else
			stack1.push(Datum(secondDatum / firstDatum));
	}

	else if(input == "mod")
	{
		if(firstDatum == 0)
			cerr << "Error: division by 0\n";
		else
			stack1.push(Datum(secondDatum % firstDatum));
	}
}




// Parameters: current input (string)
// Returns: nothing
// Sorts the input based to the appropriate processing function
void RPNCalc::comparisonOps(string input)
{
	if(input == "==")
		equalityHelper();
	else
	{
		if(stack1.top().isInt() == false)
			cerr << "Error: datum_not_int\n";
		else
		{
			int firstDatum = stack1.top().getInt();
			stack1.pop();

			if(stack1.isEmpty() == true)
				cerr << "Error: empty_stack\n";
			else if(stack1.top().isInt() == false)
				cerr << "Error: datum_not_int\n";
			else
			{				
				int secondDatum = stack1.top().getInt();
				stack1.pop();

				comparisonOpsCheck(firstDatum, secondDatum, input);
			}
		}
	}
}



// Parameters: none
// Returns: nothing
// determines if the top two datums on the stack are equal or not
void RPNCalc::equalityHelper()
{
	Datum firstDatum = stack1.top();

	stack1.pop();

	if(stack1.isEmpty() == true)
			cerr << "Error: empty_stack\n";
	else
	{		
		Datum secondDatum = stack1.top();
		stack1.pop();

		stack1.push(Datum(secondDatum == firstDatum));
	}
}


// Parameters:  top two datums on stack (ints), current input (string)
// Returns: nothing
// performs a comparison operation on the top two integers in the stack
void RPNCalc::comparisonOpsCheck(int firstDatum, int secondDatum, string input)
{
	if(input == "<")
		stack1.push(Datum(secondDatum < firstDatum));
	else if(input == ">")
	{	
		stack1.push(Datum(!(secondDatum < firstDatum) && 
			!(secondDatum == firstDatum)));
	}
	else if(input == "<=")
	{
		stack1.push(Datum(secondDatum < firstDatum || 
			secondDatum == firstDatum));
	}
	else if(input == ">=")
		stack1.push(Datum(!(secondDatum < firstDatum)));
}

// Parameters: current istream (istream&)
// Returns: nothing
// Opens target file and passes ifstream to readAndProcess()
void RPNCalc::fileHelper(istream& stream)
{
	string   filename;
    ifstream   infile;
    stream >> filename;
    infile.open(filename.c_str());
    
    if (not infile.is_open()) 
    {
            cerr << "Unable to open " << filename << endl;
    }
    else
    {
    	readAndProcess(infile);
    }

    infile.close();
}



// Parameters: current istream (istream&)
// Returns: nothing
// pushes parsed code block onto the stack
void RPNCalc::codeBlockHelper(istream &input)
{
	string parsedCodeBlock;

	parsedCodeBlock = parseCodeBlock(input);

	stack1.push(Datum(parsedCodeBlock));
}





// Parameters: current istream (istream&)
// Returns: parsed code block (string)
// parses a given code block (removes outer-most curly braces)
string RPNCalc::parseCodeBlock(istream &input)
{
	string convertedString;
	int numOpenBraces = 1;
	int numClosedBraces = 0;

	string blockData;    
    do {
    	input >> blockData;

    	if(blockData == "{")
    		numOpenBraces++;
    	else if(blockData == "}")
    	{
    		numClosedBraces++;
    		if (numOpenBraces == numClosedBraces)
    			break;
    	}
    	if( !( (blockData == "{" && numOpenBraces == 1) )  )
    	{
    		convertedString += blockData;
    		convertedString += " ";
    	}  	
    } while(numOpenBraces != numClosedBraces);

    //return convertedString.substr(0, convertedString.length() - 1);
    return convertedString;
}


// Parameters: none
// Returns: nothing
// executes a code block on top of the stack
void RPNCalc::execHelper()
{
	if(stack1.top().isCodeBlock() == false)
	{
		cerr << "Error: cannot execute non codeblock\n";
	}
	else
	{
		stringstream ss;

		Datum d = stack1.top();

		stack1.pop();

		ss << d.getCodeBlock();;

		readAndProcess(ss);
	}
}



// Parameters: none
// Returns: nothing
// Checks if the 'if' function can be applied given the stack's current state
void RPNCalc::ifChecker()
{
	if(stack1.top().isCodeBlock() == false)	
		cerr << "Error: expected codeblock in if branch\n";
	else
	{
		string falseCase = stack1.top().getCodeBlock();
		stack1.pop();
		if(stack1.isEmpty() == true)
			cerr << "Error: empty_stack\n";
		else if(stack1.top().isCodeBlock() == false)	
			cerr << "Error: expected codeblock in if branch\n";
		else
		{
			string trueCase = stack1.top().getCodeBlock();
			stack1.pop();
			if(stack1.isEmpty() == true)
				cerr << "Error: empty_stack\n";
			else if(stack1.top().isBool() == false)
				cerr << "Error: datum_not_bool\n";
			else
			{
				bool condition = stack1.top().getBool();
				ifHelper(trueCase, falseCase, condition);
			}
		}
	}
}


// Parameters: true case (string), false case (string), condition (bool)
// Returns: nothing
// Performs 'if' function on top three elements of stack (as specified
// by project spec)
void RPNCalc::ifHelper(string trueCase, string falseCase, bool condition)
{
	if (condition == true)
	{
		stack1.pop();
		stack1.push(Datum(trueCase));
		execHelper();
	}
	if (condition == false)
	{
		stack1.pop();
		stack1.push(Datum(falseCase));
		execHelper();
	}
}




