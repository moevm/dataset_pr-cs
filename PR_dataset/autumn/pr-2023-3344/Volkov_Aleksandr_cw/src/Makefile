CC = gcc -c

all: cw

cw: cw.o processFunc.o ioFunc.o
	gcc cw.o processFunc.o ioFunc.o -o cw

cw.o: cw.c processFunc.h ioFunc.h structures.h
	$(CC) cw.c

processFunc.o: processFunc.c processFunc.h structures.h
	$(CC) processFunc.c

ioFunc.o: ioFunc.c ioFunc.h structures.h
	$(CC) ioFunc.c

clean:
	rm *.o