
CC = gcc
CFLAGS = -Wall -std=c99
all: menu clean

menu: menu.o abs_max.o abs_min.o diff.o sum.o output.o scan_array.o
	$(CC) menu.o abs_max.o abs_min.o diff.o sum.o output.o scan_array.o -o menu
menu.o: menu.c output.h scan_array.h
	$(CC) -c menu.c $(CFLAGS)

abs_max.o: abs_max.c abs_max.h
	$(CC) -c abs_max.c $(CFLAGS)

abs_min.o: abs_min.c abs_min.h
	$(CC) -c abs_min.c $(CFLAGS)

diff.o: diff.c diff.h
	$(CC) -c diff.c $(CFLAGS)

sum.o: sum.c sum.h
	$(CC) -c sum.c $(CFLAGS)

output.o: output.c output.h abs_max.h abs_min.h diff.h sum.h
	$(CC) -c output.c $(CFLAGS)

scan_array.o: scan_array.c scan_array.h
	$(CC) -c scan_array.c $(CFLAGS)

clean:
	rm -f *.o
