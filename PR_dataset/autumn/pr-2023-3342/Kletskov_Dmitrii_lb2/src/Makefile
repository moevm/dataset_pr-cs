CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: menu

menu: menu.o diff.o max.o min.o sum.o
	$(CC) $(CFLAGS) -o menu menu.o diff.o max.o min.o sum.o

menu.o: menu.c
	$(CC) $(CFLAGS) -c menu.c

diff.o: diff.c diff.h
	$(CC) $(CFLAGS) -c diff.c

max.o: max.c max.h
	$(CC) $(CFLAGS) -c max.c

min.o: min.c min.h
	$(CC) $(CFLAGS) -c min.c

sum.o: sum.c sum.h
	$(CC) $(CFLAGS) -c sum.c

clean:
	rm -f *.o menu
