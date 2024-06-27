all: menu.o data_reading.o index_first_zero.o index_last_zero.o sum_abs.o sum_between.o sum_before_and_after.o output_answer.o choice_answer.o
	gcc menu.o data_reading.o index_first_zero.o index_last_zero.o sum_abs.o sum_between.o sum_before_and_after.o output_answer.o choice_answer.o -o menu
menu.o: menu.c choice_answer.h data_reading.h
	gcc -c -std=c99 menu.c
data_reading.o: data_reading.c data_reading.h
	gcc -c -std=c99 data_reading.c
index_first_zero.o: index_first_zero.c index_first_zero.h
	gcc -c -std=c99 index_first_zero.c
index_last_zero.o: index_last_zero.c index_last_zero.h
	gcc -c -std=c99 index_last_zero.c
sum_abs.o: sum_abs.c sum_abs.h
	gcc -c -std=c99 sum_abs.c
sum_between.o: sum_between.c sum_abs.h index_first_zero.h index_last_zero.h sum_between.h
	gcc -c -std=c99 sum_between.c
sum_before_and_after.o: sum_before_and_after.c sum_abs.h index_first_zero.h index_last_zero.h sum_before_and_after.h
	gcc -c -std=c99 sum_before_and_after.c
output_answer.o: output_answer.c output_answer.h
	gcc -c -std=c99 output_answer.c	
choice_answer.o: choice_answer.c output_answer.h choice_answer.h
	gcc -c -std=c99 choice_answer.c