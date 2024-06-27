all: cw clean

cw: main.o FunctionText.o FunctionObrText.o FreeMemory.o Function1.o Function8.o FreeMemory1.o Function2.o Function3.o Function4.o OutText.o OutFunc1.o
	gcc main.o FunctionText.o FunctionObrText.o FreeMemory.o Function1.o Function8.o FreeMemory1.o Function2.o Function3.o Function4.o OutText.o OutFunc1.o -o cw

main.o: main.c Common.h Function1.h Function8.h Function2.h Function3.h Function4.h FunctionText.h FunctionObrText.h FreeMemory.h FreeMemory1.h OutText.h OutFunc1.h
	gcc -c main.c

FunctionText.o: FunctionText.c FunctionText.h Common.h
	gcc -c FunctionText.c

FunctionObrText.o: FunctionObrText.c FunctionObrText.h Common.h
	gcc -c FunctionObrText.c

FreeMemory.o: FreeMemory.c FreeMemory.h
	gcc -c FreeMemory.c

Function1.o: Function1.c Function1.h Common.h 
	gcc -c Function1.c

Function8.o: Function8.c Function8.h Common.h 
	gcc -c Function8.c

FreeMemory1.o: FreeMemory1.c FreeMemory1.h Common.h
	gcc -c FreeMemory1.c

Function2.o: Function2.c Function2.h Common.h
	gcc -c Function2.c

Function3.o: Function3.c Function3.h Common.h
	gcc -c Function3.c

Function4.o: Function4.c Function4.h Common.h
	gcc -c Function4.c

OutText.o: OutText.c OutText.h Common.h
	gcc -c OutText.c

OutFunc1.o: OutFunc1.c OutFunc1.h Common.h
	gcc -c OutFunc1.c

clean:
	rm -rf *.o main