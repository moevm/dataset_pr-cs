CC = gcc
CFLAGS = -std=c99 -Wno-multichar

all: cw

cw: main.o inputHandler.o deleting.o back.o printFunctions.o date.o sorting.o dop.o
	$(CC) $(CFLAGS) -o cw main.o inputHandler.o deleting.o back.o printFunctions.o date.o sorting.o dop.o

main.o: main.c structures.h
	$(CC) $(CFLAGS) -c main.c


printFunctions.o: printFunctions.c
	$(CC) $(CFLAGS) -c printFunctions.c

inputHandler.o: inputHandler.c structures.h
	$(CC) $(CFLAGS) -c inputHandler.c

deleting.o: deleting.c structures.h
	$(CC) $(CFLAGS) -c deleting.c

sorting.o: sorting.c printFunctions.h structures.h
	$(CC) $(CFLAGS) -c sorting.c

replacingSpecSymbols.o: date.c structures.h
	$(CC) $(CFLAGS) -c dates.c

back.o: back.c structures.h
	$(CC) $(CFLAGS) -c back.c
	
dop.o: dop.c structures.h
	$(CC) $(CFLAGS) -c dop.c	

clean:
	rm -f *.o main
