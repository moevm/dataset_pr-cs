menu : menu.o index_first_negative.o index_last_negative.o sum_before_and_after_negative.o sum_between_negative.o call_operation.o filling_the_array.o
	gcc menu.o index_first_negative.o index_last_negative.o sum_before_and_after_negative.o sum_between_negative.o call_operation.o filling_the_array.o -o menu
menu.o : menu.c call_operation.h filling_the_array.h
	gcc -c -std=c99 menu.c
index_first_negative.o : index_first_negative.c index_first_negative.h
	gcc -c -std=c99 index_first_negative.c
index_last_negative.o : index_last_negative.c index_last_negative.h
	gcc -c -std=c99 index_last_negative.c
sum_before_and_after_negative.o : sum_before_and_after_negative.c sum_before_and_after_negative.h index_first_negative.h index_last_negative.h
	gcc -c -std=c99 sum_before_and_after_negative.c
sum_between_negative.o : sum_between_negative.c sum_between_negative.h index_first_negative.h index_last_negative.h
	gcc -c -std=c99 sum_between_negative.c
call_operation.o : call_operation.c call_operation.h sum_between_negative.h index_first_negative.h index_last_negative.h sum_before_and_after_negative.h
	gcc -c -std=c99 call_operation.c
filling_the_array.o : filling_the_array.c filling_the_array.h
	gcc -c -std=c99 filling_the_array.c
clean:
	rm menu *.o

	
