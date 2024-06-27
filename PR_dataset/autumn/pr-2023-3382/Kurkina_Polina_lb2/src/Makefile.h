all: menu.o index_first_negative.o index_last_negative.o sum_between_negative.o sum_before_and_after_negative.o Solution.o 
	gcc menu.o index_first_negative.o index_last_negative.o sum_between_negative.o sum_before_and_after_negative.o Solution.o -o menu
menu.o: menu.o menu.c index_first_negative.h index_last_negative.h sum_between_negative.h sum_before_and_after_negative.h Solution.h
	gcc -c -std=c99 menu.c
index_first_negative.o: index_first_negative.h index_first_negative.c
	gcc -c -std=c99 index_first_negative.c

index_last_negative.o: index_last_negative.h index_last_negative.c
	gcc -c -std=c99 index_last_negative.c

sum_between_negative.o: sum_between_negative.h sum_between_negative.c
	gcc -c -std=c99 sum_between_negative.c

sum_before_and_after_negative.o: sum_before_and_after_negative.h sum_before_and_after_negative.c
	gcc -c -std=c99 sum_before_and_after_negative.c

Solution.o: Solution.h Solution.c
	gcc -c -std=c99 Solution.c