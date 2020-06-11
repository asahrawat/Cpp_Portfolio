###########################################################################
##                  Makefile for PROJ2    (gerp)                         ##
###########################################################################
#
# 

CXX = clang++
CXXFLAGS = -g3 -O2 -std=c++11 -Wall -Wextra
LDFLAGS = -g3

gerp: DirNode.o FSTree.o wordTable.o gerpSearch.o main.o
	${CXX} ${LDFLAGS} -o gerp DirNode.o FSTree.o wordTable.o gerpSearch.o main.o


wordTable.o: wordNode.h wordTable.h wordTable.cpp
gerpSearch.o: wordNode.h wordTable.h FSTree.h DirNode.h gerpSearch.h \
	gerpSearch.cpp
main.o: wordNode.h wordTable.h FSTree.h DirNode.h gerpSearch.h main.cpp



clean:
	rm -rf gerp *.o *.dSYM

provide:
	provide comp15 proj2part3 FSTree.h DirNode.h wordNode.h wordTable.h \
							wordTable.cpp gerpSearch.h gerpSearch.cpp \
								testWordTable.cpp testGerpSearch.cpp \
								README Makefile commands.txt main.cpp
