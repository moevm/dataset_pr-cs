CC = gcc
CFLAGS = -std=c99

all: menu

menu: menu.o index_first_zero.o index_last_zero.o sum_between.o sum_before_and_after.o
	$(CC) $^ -o menu $(CFLAGS)

menu.o: menu.c
	$(CC) -c $< -o $@ $(CFLAGS)

index_first_zero.o: index_first_zero.c index_first_zero.h
	$(CC) -c $< -o $@ $(CFLAGS)

index_last_zero.o: index_last_zero.c index_last_zero.h
	$(CC) -c $< -o $@ $(CFLAGS)

sum_between.o: sum_between.c sum_between.h index_first_zero.h index_last_zero.h
	$(CC) -c $< -o $@ $(CFLAGS)

sum_before_and_after.o: sum_before_and_after.c sum_before_and_after.h index_first_zero.h index_last_zero.h
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f *.o menu

