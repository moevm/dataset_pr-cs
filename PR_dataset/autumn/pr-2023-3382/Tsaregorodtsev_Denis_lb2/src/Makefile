all: menu.o index_first_even.o index_last_odd.o sum_between_even_odd.o sum_before_even_and_after_odd.o
	gcc menu.o index_first_even.o index_last_odd.o sum_between_even_odd.o sum_before_even_and_after_odd.o -o menu

main.0: menu.c
	gcc -c menu.c

index_first_even.o: index_first_even.c
	gcc -c index_first_even.c

index_last_odd.o: index_last_odd.c
	gcc -c index_last_odd.c

sum_between_even_odd.o: sum_between_even_odd.c
	gcc -c sum_between_even_odd.c

sum_before_even_and_after_odd.o: sum_before_even_and_after_odd.c
	gcc -c sum_before_even_and_after_odd.c
