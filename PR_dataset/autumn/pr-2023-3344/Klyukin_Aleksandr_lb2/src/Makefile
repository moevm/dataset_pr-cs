all: menu.o
	gcc -o menu *.o -std=c99

menu.o: *.c
	gcc -c *.c -std=c99

index_first_negative.o: index_first_negative.h index_first_negative.c
	gcc -c index_first_negative.c -std=c99

index_last_negative.o: index_first_negative.h index_last_negative.c
	gcc -c index_last_negative.c -std=c99

sum_between_negative.o: index_first_negative.h index_last_negative.h sum_between_negative.h sum_between_negative.c
	gcc -c sum_between_negative.c -std=c99

sum_before_and_after_negative.o: index_first_negative.h index_last_negative.h sum_before_and_after_negative.h sum_before_and_after_negative.c
	gcc -c sum_before_and_after_negative.c -std=c99

clean:
	rm *.o