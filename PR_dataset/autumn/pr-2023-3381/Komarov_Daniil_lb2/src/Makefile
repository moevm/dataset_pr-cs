all: menu.o index_first_zero.o index_last_zero.o sum_between.o sum_before_and_after.o
	gcc *.o -o menu

%.o: %.c
	gcc -Wall -std=c99 -c $< -o $@

clean:
	rm -f *.o

rebuld: clean all
