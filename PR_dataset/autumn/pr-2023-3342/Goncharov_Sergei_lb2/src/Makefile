CC=-c -std=c99

all: menu.o index_first_even.o index_last_odd.o sum_before_even_and_after_odd.o sum_between_even_odd.o input.o output.o
		gcc menu.o index_first_even.o index_last_odd.o sum_before_even_and_after_odd.o sum_between_even_odd.o input.o output.o -o menu

menu.o: menu.c index_first_even.h index_last_odd.h sum_between_even_odd.h sum_before_even_and_after_odd.h
		gcc $(CC) menu.c

input.o: input.c input.h
		gcc $(CC) input.c

output.o: output.c index_first_even.h index_last_odd.h sum_before_even_and_after_odd.h sum_between_even_odd.h output.h
		gcc $(CC) output.c

index_first_even.o: index_first_even.c index_first_even.h
		gcc $(CC) index_first_even.c


index_last_odd.o: index_last_odd.c index_last_odd.h
		gcc $(CC) index_last_odd.c

sum_before_even_and_after_odd.o: sum_before_even_and_after_odd.c sum_between_even_odd.h index_first_even.h index_last_odd.h
		gcc $(CC) sum_before_even_and_after_odd.c

sum_between_even_odd.o: sum_between_even_odd.c sum_before_even_and_after_odd.h sum_between_even_odd.h index_first_even.h index_last_odd.h
		gcc $(CC) sum_between_even_odd.c
		
clean : 
	rm menu *.o
