all: menu

menu: menu.o index_first_even.o index_last_odd.o sum_between_even_odd.o sum_before_even_and_after_odd.o
        gcc menu.o index_first_even.o index_last_odd.o sum_between_even_odd.o sum_before_even_and_after_odd.o -o menu

menu.o: menu.c index_first_even.h index_last_odd.h sum_between_even_odd.h sum_before_even_and_after_odd.h
        gcc -std=c99 -c menu.c

index_first_even.o: index_first_even.c
        gcc -std=c99 -c index_first_even.c

index_last_odd.o: index_last_odd.c
        gcc -std=c99 -c index_last_odd.c

sum_between_even_odd.o: sum_between_even_odd.c index_first_even.h index_last_odd.h
        gcc -std=c99 -c sum_between_even_odd.c

sum_before_even_and_after_odd.o: sum_before_even_and_after_odd.c index_first_even.h index_last_odd.h
        gcc -std=c99 -c sum_before_even_and_after_odd.c

clean:
        rm -rf *.o menu
