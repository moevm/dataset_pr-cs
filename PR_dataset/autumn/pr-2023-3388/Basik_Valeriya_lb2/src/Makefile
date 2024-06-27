CC=gcc
CFLAGS=-c -Wall -std=c99

all: menu

menu: menu.o index_first_negative.o index_last_negative.o sum_before_and_after_negative.o sum_between_negative.o
	$(CC) menu.o index_first_negative.o index_last_negative.o sum_before_and_after_negative.o sum_between_negative.o -o menu

menu.o: menu.c
	$(CC) $(CFLAGS) menu.c

index_first_negative.o: index_first_negative.c
	$(CC) $(CFLAGS) index_first_negative.c

index_last_negative.o: index_last_negative.c
	$(CC) $(CFLAGS) index_last_negative.c

sum_before_and_after_negative.o: sum_before_and_after_negative.c
	$(CC) $(CFLAGS) sum_before_and_after_negative.c

sum_between_negative.o: sum_between_negative.c
	$(CC) $(CFLAGS) sum_between_negative.c

clean:
	rm -rf *.o menu