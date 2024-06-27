menu: menu.o index_first_even.o index_last_odd.o sum_before_even_and_after_odd.o sum_between_even_odd.o print_func.o scan_func.o MAIN_HEADERS.o
	gcc menu.o index_first_even.o index_last_odd.o sum_before_even_and_after_odd.o sum_between_even_odd.o print_func.o scan_func.o -o menu

menu.o: menu.c print_func.h scan_func.h
	gcc -c menu.c

index_first_even.o: index_first_even.c index_first_even.h
	gcc -c index_first_even.c

index_last_odd.o: index_last_odd.c index_last_odd.h
	gcc -c index_last_odd.c

sum_before_even_and_after_odd.o: sum_before_even_and_after_odd.c sum_before_even_and_after_odd.h
	gcc -c sum_before_even_and_after_odd.c

sum_between_even_odd.o: sum_between_even_odd.c sum_between_even_odd.h
	gcc -c sum_between_even_odd.c

print_func.o: print_func.c print_func.h
	gcc -c print_func.c

scan_func.o: scan_func.c scan_func.h
	gcc -c scan_func.c

MAIN_HEADERS.o: MAIN_HEADERS.h
	touch MAIN_HEADERS.o

clean:
	rm menu *.o
