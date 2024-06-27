all: menu

menu: menu.o index_first_even.o index_last_odd.o sum_between_even_odd.o sum_before_even_and_after_odd.o
	gcc menu.o index_first_even.o index_last_odd.o sum_between_even_odd.o sum_before_even_and_after_odd.o -o menu

menu.o:
	gcc -c menu.c -std=c99

index_first_even.o:
	gcc -c index_first_even.c -std=c99

index_last_odd.o:
	gcc -c index_last_odd.c -std=c99

sum_between_even_odd.o:
	gcc -c sum_between_even_odd.c -std=c99

sum_before_even_and_after_odd.o:
	gcc -c sum_before_even_and_after_odd.c -std=c99