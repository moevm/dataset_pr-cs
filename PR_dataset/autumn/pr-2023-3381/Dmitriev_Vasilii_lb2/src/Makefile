all: fill_array_and_get_len.o get_one_int.o index_first_zero.o index_last_zero.o menu.o search_index_zero.o sum_before_and_after.o sum_between.o sum_elements.o
	gcc fill_array_and_get_len.o get_one_int.o index_first_zero.o index_last_zero.o menu.o search_index_zero.o sum_before_and_after.o sum_between.o sum_elements.o -o menu

fill_array_and_get_len.o: fill_array_and_get_len.c fill_array_and_get_len.h
	gcc -c fill_array_and_get_len.c -o fill_array_and_get_len.o
        
index_first_zero.o: index_first_zero.c index_first_zero.h search_index_zero.h
	gcc -c index_first_zero.c -o index_first_zero.o
        
index_last_zero.o: index_last_zero.c index_last_zero.h search_index_zero.h
	gcc -c index_last_zero.c -o index_last_zero.o
        
search_index_zero.o: search_index_zero.c search_index_zero.h
	gcc -c search_index_zero.c -o search_index_zero.o

sum_before_and_after.o: sum_before_and_after.c sum_before_and_after.h sum_elements.h index_first_zero.h index_last_zero.h
	gcc -c sum_before_and_after.c -o sum_before_and_after.o

sum_between.o: sum_between.c sum_between.h sum_elements.h index_first_zero.h index_last_zero.h
	gcc -c sum_between.c -o sum_between.o
        
sum_elements.o: sum_elements.c sum_elements.h
	gcc -c sum_elements.c -o sum_elements.o

get_one_int.o: get_one_int.c get_one_int.h
	gcc -c get_one_int.c -o get_one_int.o
        
menu.o: menu.c index_first_zero.h index_last_zero.h sum_between.h sum_before_and_after.h fill_array_and_get_len.h get_one_int.h
	gcc -c menu.c -o menu.o
