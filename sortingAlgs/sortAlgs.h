/*
 *  Responsible for the function declarations and parameters of each sorting 
 *  algorithm
 *
 *
 *  Homework 5: All Sorts of Sorta Nice Sortin' Algorithms
 *
 *  sortAlgs.h
 *  Header for sortAlgs.cpp
 *  Modified By (UTLN): asahra01
 *
 */

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

// Parameters: unsorted vector (reference to vector)
// Returns: none
// sorts the vector by the insertion sort algorithm
void insertionSort(vector<int> &);


// Parameters: unsorted vector (reference to vector)
// Returns: none
// calls the quickSortHelper function to apply the quick sort algorithm
void quickSort(vector<int> &);



// Parameters: unsorted vector (reference to vector)
// Returns: none
// calls the quickSortHelper function to apply the shell sort algorithm
void shellSort(vector<int> &);
