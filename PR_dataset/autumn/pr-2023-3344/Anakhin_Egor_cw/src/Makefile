CC = gcc
CFLAGS = -std=c99 -Wno-multichar

all: cw

cw: main.o inputHandler.o deleting.o palindromsFinder.o printFunctions.o replacingSpecSymbols.o sorting.o new_func.o
	$(CC) $(CFLAGS) -o cw main.o inputHandler.o deleting.o palindromsFinder.o printFunctions.o replacingSpecSymbols.o sorting.o new_func.o

main.o: main.c structures.h
	$(CC) $(CFLAGS) -c main.c

new_func.o: new_func.c structures.h
	$(CC) $(CFLAGS) -c new_func.c

printFunctions.o: printFunctions.c
	$(CC) $(CFLAGS) -c printFunctions.c

inputHandler.o: inputHandler.c structures.h
	$(CC) $(CFLAGS) -c inputHandler.c

deleting.o: deleting.c structures.h
	$(CC) $(CFLAGS) -c deleting.c

sorting.o: sorting.c printFunctions.h structures.h
	$(CC) $(CFLAGS) -c sorting.c

replacingSpecSymbols.o: replacingSpecSymbols.c structures.h
	$(CC) $(CFLAGS) -c replacingSpecSymbols.c

palindromsFinder.o: palindromsFinder.c structures.h
	$(CC) $(CFLAGS) -c palindromsFinder.c

clean:
	rm -f *.o main