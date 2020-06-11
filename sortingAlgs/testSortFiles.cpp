#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string>
#include "sortAlgs.h"

using namespace std;

int main()
{
	ofstream outfile;

	string filename1 = "forwardOrder.txt";
	string filename2 = "reverseOrder.txt";
	string filename3 = "randomOrder.txt";

	outfile.open(filename1.c_str());
	for(int i = 1; i <= 100000; i++)
	{
		outfile << i << endl;
	}
	outfile.close();

	outfile.open(filename2.c_str());
	for(int i = 0; i < 100000; i++)
	{
		outfile << 100000 - i << endl;
	}
	outfile.close();

	outfile.open(filename3.c_str());
	for(int i = 0; i < 100000; i++)
	{
		outfile << rand() % 100000 + 1 << endl;
	}
	outfile.close();
}