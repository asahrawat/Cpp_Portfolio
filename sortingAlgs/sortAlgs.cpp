/*
 *  Responsible for handling the implementation of each sorting algorithm
 *
 *
 *  Homework 5: All Sorts of Sorta Nice Sortin' Algorithms
 *
 *  sortAlgs.cpp
 *  Complete implementation of sorting algorithms
 *  Modified By (UTLN): asahra01
 *           On       : 10/31/17
 *
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include "sortAlgs.h"

using namespace std;

void quickSortHelper(vector<int> &, int, int);
void shellHelper(vector<int> &v1, int numElem);

// Parameters: unsorted vector (reference to vector)
// Returns: none
// sorts the vector by the insertion sort algorithm
void insertionSort(vector<int> &v1)
{
	if(v1.size() == 1 || v1.empty() == true)
		return;
	else
	{
		int temp1, temp2;  // sacrifice on run time for correct order list
		for(int i = 1; i < (int) v1.size(); i++)
		{
			temp1 = i;
			while(v1[temp1] < v1[temp1 - 1] && temp1 > 0)
			{
				temp2 = v1[temp1];
				v1[temp1] = v1[temp1 - 1];
				v1[temp1 - 1] = temp2;
				temp1--;
			}	
		}
	}
}



// Parameters: unsorted vector (reference to vector)
// Returns: none
// calls the quickSortHelper function
void quickSort(vector<int> &v1)
{
	quickSortHelper(v1, 0, (int) v1.size() - 1);
}




// Parameters: vector to be sorted (reference to vector), left wall (int), 
// right wall (int)
// Returns: none
// sorts the vector by the quick sort algorithm
void quickSortHelper(vector<int> &vec1, int left, int right)
{
	int low = left;
	int high = right;
	int middleIndex = (left + right) / 2;
	int pivot = vec1[middleIndex];
	while(low <= high)
	{
		int temp1;
		while(vec1[low] < pivot)
			low++;

		while(vec1[high] > pivot)
			high--;

		if(low <= high)
		{	
			temp1 = vec1[high];
			vec1[high] = vec1[low];
			vec1[low] = temp1;
			high--;
			low++;
		}
	}
	if(left < high)
		quickSortHelper(vec1, left, high);
	if(right > low)
		quickSortHelper(vec1, low, right);
	else
		return;
}



// Parameters: unsorted vector (reference to vector)
// Returns: none
// calls the quickSortHelper function
void shellSort(vector<int> &v1)
{
	shellHelper(v1, (int) v1.size() - 1);
}



// Parameters: unsorted vector (reference to vector) 
// Returns: none
// sorts the vector by the shell sort algorithm
void shellHelper(vector<int> &v1, int numElem)
{
	for(int gap = numElem / 2; gap > 0; gap = gap / 2)
	{
		for(int i = gap; i <= numElem; i++)
		{
			int temp1, temp2;
			temp1 = i;
			while(temp1 >= gap && v1[temp1] < v1[temp1 - gap])
			{
				temp2 = v1[temp1];
				v1[temp1] = v1[temp1 - gap];
				v1[temp1 - gap] = temp2;
				temp1 = temp1 - gap;
			}	
		}
	}
}




