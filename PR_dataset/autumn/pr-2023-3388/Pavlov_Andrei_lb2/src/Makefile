all: menu.o io_routine.o index_first_zero.o index_last_zero.o sum.o sum_between.o sum_before_and_after.o
	gcc menu.o io_routine.o index_first_zero.o index_last_zero.o sum.o sum_between.o sum_before_and_after.o -o menu
menu.o: menu.c io_routine.h index_first_zero.h index_last_zero.h sum_between.h sum_before_and_after.h
	gcc -c -std=c99 menu.c
io_routine.o: io_routine.c io_routine.h
	gcc -c -std=c99 io_routine.c
index_first_zero.o: index_first_zero.c index_first_zero.h
	gcc -c -std=c99 index_first_zero.c
index_last_zero.o: index_last_zero.c index_last_zero.h
	gcc -c -std=c99 index_last_zero.c
sum.o: sum.c sum.h
	gcc -c -std=c99 sum.c
sum_between.o: sum_between.c sum.h index_first_zero.h index_last_zero.h sum_between.h
	gcc -c -std=c99 sum_between.c
sum_before_and_after.o: sum_before_and_after.c sum.h index_first_zero.h index_last_zero.h sum_before_and_after.h
	gcc -c -std=c99 sum_before_and_after.c

