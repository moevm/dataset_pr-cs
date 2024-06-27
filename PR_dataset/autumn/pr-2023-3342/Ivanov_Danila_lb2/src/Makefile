CC=gcc
CFLAGS=-c -std=c99

all: menu.o index_first_negative.o index_last_negative.o sum_between_negative.o sum_before_and_after_negative.o output.o input.o
	$(CC) menu.o index_first_negative.o index_last_negative.o sum_between_negative.o sum_before_and_after_negative.o output.o input.o -o menu

menu.o: menu.c output.h input.h
	$(CC) $(CFLAGS)  menu.c

index_first_negative.o: index_first_negative.c index_first_negative.h
	$(CC) $(CFLAGS)   index_first_negative.c

index_last_negative.o: index_last_negative.c index_last_negative.h
	$(CC) $(CFLAGS)  index_last_negative.c

sum_between_negative.o: sum_between_negative.c index_last_negative.h index_first_negative.h sum_between_negative.h
	$(CC) $(CFLAGS)  sum_between_negative.c

sum_before_and_after_negative.o: sum_before_and_after_negative.c index_last_negative.h index_first_negative.h sum_before_and_after_negative.h
	$(CC) $(CFLAGS)  sum_before_and_after_negative.c

output.o: output.c output.h index_first_negative.h index_last_negative.h sum_between_negative.h sum_before_and_after_negative.h
	$(CC) $(CFLAGS)  output.c

input.o: input.c input.h
	$(CC) $(CFLAGS)  input.c