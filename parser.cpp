/*
 *  Implementation of the parseCodeBlock function, used to parse the 
 *  code block Datum type
 *  
 *
 *
 *  COMP 15 Proj 1 CalcYouLater - Reverse Polish Notation Arithmetic
 *
 *  parser.cpp
 *  parseCodeBlock function implementation
 *  Modified By (UTLN): asahra01
 *           On       : 10/1/17
 *
 */

#include<iostream>
#include<fstream>


using namespace std;

string parseCodeBlock(istream &input);


string parseCodeBlock(istream &input)
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

    return convertedString.substr(0, convertedString.length() - 1);
}




// Main to test parser function. Kept in (but commented out) for potential 
// future debugging.

/*
int main()
{
	string   filename;
    ifstream   infile;
    filename = "codeBlockTest.cpp";
    infile.open(filename.c_str());
    cout << parseCodeBlock(infile) << endl;


	//cout << parseCodeBlock(cin) << endl;

	return 0;

}
*/


