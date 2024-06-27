all: menu.o input.o output.o index_negative.o summ_arr.o index_first_negative.o index_last_negative.o sum_between_negative.o sum_before_and_after_negative.o
	gcc menu.o input.o output.o index_negative.o summ_arr.o index_first_negative.o index_last_negative.o sum_between_negative.o sum_before_and_after_negative.o -o menu

main.o: menu.c input.h output.h
	gcc -c menu.c

input.o: input.c input.h
	gcc -c input.c

output.o: output.c output.h index_first_negative.h index_last_negative.h sum_between_negative.h sum_before_and_after_negative.h
	gcc -c output.c

index_negative.o: index_negative.c index_negative.h
	gcc -c index_negative.c

summ_arr.o: summ_arr.c summ_arr.h
	gcc -c -std=c99 summ_arr.c

index_first_negative.o: index_first_negative.c index_first_negative.h index_negative.h
	gcc -c index_first_negative.c

index_last_negative.o: index_last_negative.c index_last_negative.h index_negative.h
	gcc -c index_last_negative.c

sum_between_negative.o: sum_between_negative.c sum_between_negative.h index_first_negative.h index_last_negative.h index_negative.h
	gcc -c sum_between_negative.c

sum_before_and_after_negative.o: sum_before_and_after_negative.c sum_before_and_after_negative.h index_first_negative.h index_last_negative.h index_negative.h
	gcc -c sum_before_and_after_negative.c

clear:
	rm -rf *.o
