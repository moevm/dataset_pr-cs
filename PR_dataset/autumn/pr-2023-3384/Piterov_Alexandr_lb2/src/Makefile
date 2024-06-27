
EXEC=menu
CC=gcc
CFLAGS=-c -std=c99 -Wall # -std=c99 добавлено по указанию gcc на task.moevm

all: menu.o index_first_even.o index_last_odd.o sum_between_even_odd.o sum_before_even_and_after_odd.o
	$(CC) menu.o index_first_even.o index_last_odd.o sum_between_even_odd.o sum_before_even_and_after_odd.o -o $(EXEC) 

menu.o: index_first_even.h index_last_odd.h sum_between_even_odd.h sum_before_even_and_after_odd.h
	$(CC) $(CFLAGS) menu.c

index_first_even.o: index_first_even.c index_first_even.h
	$(CC) $(CFLAGS) index_first_even.c

index_last_odd.o: index_last_odd.c index_last_odd.h
	$(CC) $(CFLAGS) index_last_odd.c

sum_between_even_odd.o: sum_between_even_odd.c sum_between_even_odd.h index_first_even.h index_last_odd.h
	$(CC) $(CFLAGS) sum_between_even_odd.c

sum_before_even_and_after_odd.o: sum_before_even_and_after_odd.c sum_before_even_and_after_odd.h index_first_even.h index_last_odd.h
	$(CC) $(CFLAGS) sum_before_even_and_after_odd.c

clear:
	rm -rf *.o
