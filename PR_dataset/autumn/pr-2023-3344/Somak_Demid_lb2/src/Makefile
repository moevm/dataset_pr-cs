all: menu.o
	gcc *.o -o menu -std=c99

menu.o: *.c
	gcc -c *.c -std=c99

index_first_zero.o: index_first_zero.c index_first_zero.h
	gcc -c index_first_zero.c -std=c99

index_last_zero.o: index_last_zero.c index_last_zero.h
	gcc -c index_last_zero.c -std=c99

sum_between.o: index_first_zero.h index_last_zero.h sum_between.h sum_between.c
	gcc -c sum_between.c -std=c99

sum_before_and_after.o: index_first_zero.h index_last_zero.h sum_before_and_after.h sum_before_and_after.c
	gcc -c sum_before_and_after.c -std=c99

clean:
	rm *.o
