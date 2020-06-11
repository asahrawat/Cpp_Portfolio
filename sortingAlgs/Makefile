###########################################################################
##                  Makefile for HW5    (Sorter)                         ##
###########################################################################
#
# 

CXX = clang++
CXXFLAGS = -g3 -std=c++11 -Wall -Wextra
LDFLAGS = -g3

CalcYouLater: sorter.o sortAlgs.o
	${CXX} ${LDFLAGS} -o sorter sortAlgs.o sorter.o

sortAlgs.o: sortAlgs.h sortAlgs.cpp
RPNCalc.o: sortAlgs.h sorter.cpp

clean:
	rm -rf sorter *.o *.dSYM

provide:
	provide comp15 hw5 sorter.cpp sortAlgs.cpp sortAlgs.h Makefile \
							README testSortFiles.cpp testFileShort.txt