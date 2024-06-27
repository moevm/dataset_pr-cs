CC = gcc
Cflags = -std=c99 -c
all: menu.o max.o min.o diff.o sum.o
	$(CC) menu.o max.o min.o diff.o sum.o -o menu
max.o: max.c max.h
	$(CC) $(Cflags) max.c
min.o: min.c min.h
	$(CC) $(Cflags) min.c min.h
diff.o: diff.c diff.h
	$(CC) $(Cflags) diff.c
sum.o: sum.c sum.h
	$(CC) $(Cflags) sum.c
menu.o: menu.c max.h min.h sum.h diff.h
	$(CC) $(Cflags) menu.c