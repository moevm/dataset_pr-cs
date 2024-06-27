all: menu.o index_first_zero.o index_last_zero.o sum_before_and_after.o sum_between.o
	gcc menu.o index_first_zero.o index_last_zero.o sum_before_and_after.o sum_between.o -o menu

menu.o: menu.c index_first_zero.h index_last_zero.h sum_before_and_after.h sum_between.h
	gcc -c -std=c99 menu.c -o menu.o

index_first_zero.o: index_first_zero.c index_first_zero.h
	gcc -c -std=c99 index_first_zero.c -o index_first_zero.o

index_last_zero.o: index_last_zero.c index_last_zero.h
	gcc -c -std=c99 index_last_zero.c -o index_last_zero.o

sum_before_and_after.o: sum_before_and_after.c sum_before_and_after.h
	gcc -c -std=c99 sum_before_and_after.c -o  sum_before_and_after.o

sum_between.o: sum_between.c sum_between.h
	gcc -c -std=c99 sum_between.c -o sum_between.o