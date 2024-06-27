all: menu index_first_even index_last_odd sum_between_even_odd sum_before_even_and_after_odd get_data  give_answer 
	gcc -o menu get_data.c index_first_even.o index_last_odd.o sum_between_even_odd.o sum_before_even_and_after_odd.o give_answer.o menu.o 
		
menu: menu.c give_answer.h
	gcc -c menu.c -std=c99

index_first_even: index_first_even.c
	gcc -c index_first_even.c -std=c99

index_last_odd: index_last_odd.c
	gcc -c index_last_odd.c -std=c99

sum_between_even_odd: sum_between_even_odd.c index_last_odd.h index_first_even.h
	gcc -c sum_between_even_odd.c -std=c99

sum_before_even_and_after_odd: sum_before_even_and_after_odd.c sum_between_even_odd.h
	gcc -c sum_before_even_and_after_odd.c -std=c99

get_data: get_data.c
	gcc -c get_data.c -std=c99

give_answer: give_answer.c index_last_odd.h index_first_even.h sum_between_even_odd.h sum_before_even_and_after_odd.h get_data.h
	gcc -c give_answer.c -std=c99

clean:
	rm -rf *.o
