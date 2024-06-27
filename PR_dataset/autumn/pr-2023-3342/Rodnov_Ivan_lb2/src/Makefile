CC = gcc
CFLAGS = -c -std=c99

all: index_first_zero.o index_last_zero.o sum_between.o sum_before_after.o input_arr.o switchres.o menu.o
	$(CC) index_first_zero.o index_last_zero.o sum_between.o sum_before_after.o input_arr.o switchres.o menu.o -o menu

menu.o: menu.c input_arr.h switchres.h
	$(CC) $(CFLAGS) menu.c

input_arr.o: input_arr.h
	$(CC) $(CFLAGS) input_arr.c

switchres.o: index_first_zero.h index_last_zero.h sum_between.h sum_before_after.h switchres.h
	$(CC) $(CFLAGS) switchres.c

index_first_zero.o: index_first_zero.h
	$(CC) $(CFLAGS) index_first_zero.c

index_last_zero.o: index_last_zero.h
	$(CC) $(CFLAGS) index_last_zero.c

sum_between.o: sum_between.h index_first_zero.h index_last_zero.h
	$(CC) $(CFLAGS) sum_between.c

sum_before_after.o: index_first_zero.h index_last_zero.h sum_before_after.h
	$(CC) $(CFLAGS) sum_before_after.c

