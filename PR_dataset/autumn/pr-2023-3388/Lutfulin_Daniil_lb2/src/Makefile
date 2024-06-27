all: get_numbers.o index_first_negative.o index_last_negative.o sum_before_and_after_negative.o sum_between_negative.o get_answer.o answer_case.o menu.o
	gcc get_numbers.o index_first_negative.o index_last_negative.o sum_before_and_after_negative.o sum_between_negative.o get_answer.o answer_case.o menu.o -o menu
get_numbers.o: get_numbers.h get_numbers.c 
	gcc -c get_numbers.c 
index_first_negative.o: index_first_negative.c index_first_negative.h
	gcc -c index_first_negative.c
index_last_negative.o: index_last_negative.c index_last_negative.h
	gcc -c index_last_negative.c
sum_before_and_after_negative.o: sum_before_and_after_negative.h sum_before_and_after_negative.c index_first_negative.h index_last_negative.h
	gcc -c sum_before_and_after_negative.c
sum_between_negative.o: sum_between_negative.c sum_between_negative.h index_first_negative.h index_last_negative.h
	gcc -c sum_between_negative.c
get_answer.o: get_answer.c get_answer.h
	gcc -c  get_answer.c
answer_case.o: answer_case.c answer_case.h index_first_negative.h index_last_negative.h sum_before_and_after_negative.h sum_between_negative.h
	gcc -c answer_case.c
menu.o: menu.c get_numbers.h answer_case.h answer_case.h 
	gcc -c menu.c
clean:
	rm -rf *.o