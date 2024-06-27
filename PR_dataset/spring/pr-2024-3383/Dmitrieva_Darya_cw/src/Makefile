all: main clean 

main: main.o BitMap.o checkers.o help.o
	g++ main.o BitMap.o checkers.o help.o -o cw 

main.o: main.cpp checkers.o BitMap.o help.o structs.h

checkers.o: checkers.cpp
	g++ -c checkers.cpp 

BitMap.o: BitMap.cpp BGR.h 
	g++ -c BitMap.cpp 

help.o: help.cpp
	g++ -c help.cpp 

clean: 
	rm -rf *.o main 
