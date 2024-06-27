all: cw clean

cw: main.o Input.o FreeMemory.o Function1.o Function2.o Function3.o SortFunctions.o Output.o Function9.o
	gcc main.o Input.o FreeMemory.o Function1.o Function2.o Function3.o SortFunctions.o Output.o Function9.o -o cw

main.o: main.c Input.h FreeMemory.h Function1.h Function2.h Function3.h Output.h Common.h Function9.h
	gcc -c main.c

Input.o: Input.c Input.h Common.h
	gcc -c Input.c

FreeMemory.o: FreeMemory.c FreeMemory.h
	gcc -c FreeMemory.c

Function1.o: Function1.c Function1.h Common.h
	gcc -c Function1.c

Function2.o: Function2.c Function2.h Common.h
	gcc -c Function2.c

Function3.o: Function3.c Function3.h Common.h
	gcc -c Function3.c

Function9.o: Function9.c Function9.h Common.h FreeMemory.h
	gcc -c Function9.c

SortFunctions: SortFunctions.c SortFunctions.h Common.h
	gcc -c SortFunctions.c
Output.o: Output.c Output.h
	gcc -c Output.c
clean:
	rm -rf *.o main
