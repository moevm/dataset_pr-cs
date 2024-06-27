CC=gcc
CFLAGS=-c -std=c99
all: compile clean
compile: menu.o index_first_zero.o index_last_zero.o sum_before_and_after.o sum_between.o input.o switcher.o
	$(CC) -o menu menu.o index_first_zero.o index_last_zero.o sum_before_and_after.o sum_between.o input.o switcher.o
menu.o: menu.c switcher.h input.h
	$(CC) $(CFLAGS) menu.c
index_first_zero.o: index_first_zero.c index_first_zero.h
	$(CC) $(CFLAGS) index_first_zero.c
index_last_zero.o: index_last_zero.c index_last_zero.h
	$(CC) $(CFLAGS) index_last_zero.c
sum_before_and_after.o: sum_before_and_after.c sum_before_and_after.h index_first_zero.h index_last_zero.h
	$(CC) $(CFLAGS) sum_before_and_after.c
sum_between.o: sum_between.c sum_between.h index_first_zero.h index_last_zero.h
	$(CC) $(CFLAGS) sum_between.c
input.o: input.c input.h
	$(CC) $(CFLAGS) input.c
switcher.o: switcher.c switcher.h index_first_zero.h index_last_zero.h sum_before_and_after.h sum_between.h
	$(CC) $(CFLAGS) switcher.c
clean:
	rm *.o