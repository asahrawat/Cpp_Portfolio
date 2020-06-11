###########################################################################
##                  Makefile for Proj1 (RPNCalc)                         ##
###########################################################################
#
# 

CXX = clang++
CXXFLAGS = -g3 -std=c++11 -Wall -Wextra
LDFLAGS = -g3

CalcYouLater: Datum.o DatumStack.o RPNCalc.o main.o
	${CXX} ${LDFLAGS} -o CalcYouLater Datum.o DatumStack.o RPNCalc.o main.o

DatumStack.o: Datum.h DatumStack.h DatumStack.cpp
RPNCalc.o: Datum.h DatumStack.h RPNCalc.h RPNCalc.cpp
main.o: Datum.h DatumStack.h RPNCalc.h

clean:
	rm -rf CalcYouLater *.o *.dSYM

provide:
	provide comp15 proj1 Datum.h DatumStack.h DatumStack.cpp \
							testDatumStack.cpp RPNCalc.h RPNCalc.cpp \
								testRPNCalc.cpp main.cpp README Makefile \
								testInput.txt testInput2.txt testInput3.txt
