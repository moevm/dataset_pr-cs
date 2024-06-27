CC = gcc
CFLAGS = -std=c99 -Wno-multichar

all: cw

cw: main.o initialization.o actions.o informations.o sortComp.o
	$(CC) $(CFLAGS) -o cw main.o initialization.o actions.o informations.o sortComp.o

main.o: main.c structures.h
	$(CC) $(CFLAGS) -c main.c

initialization.o: initialization.c structures.h
	$(CC) $(CFLAGS) -c initialization.c

actions.o: actions.c structures.h sortComp.h
	$(CC) $(CFLAGS) -c actions.c

informations.o: informations.c
	$(CC) $(CFLAGS) -c informations.c

sortComp.o: sortComp.c structures.h
	$(CC) $(CFLAGS) -c sortComp.c

clean:
	rm -f *.o main