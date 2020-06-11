/*
 *  Test file for testRPNCalc.cpp
 *
 *
 *  COMP 15 Proj 1 CalcYouLater - Reverse Polish Notation Arithmetic
 *
 *  testRPNCalc.cpp
 *
 *  Modified By (UTLN): asahra01
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



// uncomment the following to run tests
/*int main()
{
	RPNCalc calc1;

	calc1.run();

	return 0;
}*/



// Test for pushing numbers, bools and codeblocks on stack:
// Input: 4 8 14 17 print drop print drop print drop print drop
// Expected Output:
// 17
// 14
// 8
// 4
// Input: #t #f print drop print
// Expected Output:
// #f
// #t
// Input: { 3 1 / }
// Expected Output: { 3 1 / }

// Test for elementary operations:
// Input: 2 3 + 6 * 2 - 4 / 3 mod
// Expected Output: 
// 1

// Test for catching elementary operation errors:
// Input: + * - / mod 3 + 2 - 4 * 5 / 8 mod
// Expected Output:
// Error: empty_stack
// Error: empty_stack
// Error: empty_stack
// Error: empty_stack
// Error: empty_stack
// Error: empty_stack
// Error: empty_stack
// Error: empty_stack
// Error: empty_stack
// Error: empty_stack
// Input: 3 #t +
// Expected Output: Error: datum_not_int

// Test for (most) comparison operators
// Input: 3 4 18 4 23 9 54 8 > print drop < print drop >= print drop
// <= print
// Expected Output:
// #t
// #f
// #t
// #t
// Input: 6 { 4 1 * } >
// Expected Output: Error: datum_not_int


// Test for equivalency
// Input 1: 3 4 == print 6 6 == print #t #t == print #t #f == print
// Input 2: { 3 4 + } { 3 4 + } == print { 3 1 + } { 2 2 + } == print
// Expected output 1: #f #t #t #f
// Expected output 2: #t #f
// Input: 3 #t == print
// Expected Output: false



// Test for file (including nested file)
// Input 1: file testInput.txt
// Expected Output: #t 9

// Test for if command (simple)
// Input: 2 5 > { #f } { #t } if print
// Expected Output: #t
// Input: { 3 1 + } { 4 1 +} { 5 1 +} if 
// Expected Output: Error: datum_not_bool
// Input: { 3 1 + } 4 3 if  
// Expected Output: Error: expected codeblock in if branch


// Test for if command (complicated) (from spec)
// Input: 4 dup 10 == { 1 0 / } { 6 + 10 dup 10 < { 10 > } { 10 == } if }
// if print
// Expected Output: #t


// Test for not
// Input: #t not print
// Expected Output: #f
// Input: 4 not { 6 1 * } not
// Expected Output: Error: datum_not_bool Error: datum_not_bool


// Test for drop
// Input: #t print drop print
// Expected Ouput: #t Error: empty_stack


// Test for dup
// Input: #t dup print drop print { 4 3 + } drup print drop print
// Expected Output: #t #t { 4 3 + } { 4 3 + }
// Input: 7 dup print drop print
// Expected Output: 7 7


// Test for swap
// Input: 4 5 swap print drop print
// Expected Output: 4 5
// Input: #t { 5 3 / } swap print drop print
// Expected Output: #t { 5 3 / }


// Test for exec
// Input: { 7 1 * } exec print
// Expected Output: 7
// Input: 4 #t exec drop exec
// Expected Output: 
// Error: cannot execute non codeblock 
// Error: cannot execute non codeblock

// Test for clear
// Input: 4 3 clear +
// Expected Output: Error: empty_stack


// Most previous functions serve as 'print' test
// Codeblock pushing commands serve as '{' test
