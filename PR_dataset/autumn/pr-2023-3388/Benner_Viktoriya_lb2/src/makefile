all: menu.o input_type.o nput_array.o index_first_even.o index_last_odd.o sum_between_even_odd.o sum_before_even_and_after_odd.o switch_function.o
    gcc menu.o input_type.o nput_array.o index_first_even.o index_last_odd.o sum_between_even_odd.o sum_before_even_and_after_odd.o switch_function.o -o menu 

menu.o: menu.c index_first_even.h index_last_odd.h sum_between_even_odd.h sum_before_even_and_after_odd.h
    gcc -c -std=c99 menu.c

input_type.o: input_type.c input_type.h
    gcc -c -std=c99 input_type.c

nput_array.o: nput_array.c nput_array.h
    gcc -c -std=c99 nput_array.c

index_first_even.o: index_first_even.c index_first_even.h
    gcc -c -std=c99 index_first_even.c

index_last_odd.o: index_last_odd.c index_last_odd.h
    gcc -c -std=c99 index_last_odd.c

sum_between_even_odd.o: sum_between_even_odd.c sum_between_even_odd.h
    gcc -c -std=c99 sum_between_even_odd.c
sum_before_even_and_after_odd.o: sum_before_even_and_after_odd.c sum_before_even_and_after_odd.h
    gcc -c -std=c99 sum_before_even_and_after_odd.c
switch_function.o: switch_function.c switch_function.h
    gcc -c -std=c99 switch_function.c