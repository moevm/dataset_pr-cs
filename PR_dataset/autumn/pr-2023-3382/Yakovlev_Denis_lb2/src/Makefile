CC = gcc
CFLAGS = -c -std=c99

all: menu.o max.o min.o diff.o sum.o print_answer.o
		$(CC) menu.o max.o min.o diff.o sum.o print_answer.o -o menu

menu.o: menu.c print_answer.h
		$(CC) $(CFLAGS) menu.c

max.o: max.c max.h
		$(CC) $(CFLAGS) max.c

min.o: min.c min.h
		$(CC) $(CFLAGS) min.c

diff.o: diff.c diff.h min.h max.h
		$(CC) $(CFLAGS) diff.c

sum.o: sum.c sum.h min.h
		$(CC) $(CFLAGS) sum.c

print_answer.o: print_answer.c print_answer.h max.h min.h diff.h sum.h
		$(CC) $(CFLAGS) print_answer.c

clean:
		rm *.o menu