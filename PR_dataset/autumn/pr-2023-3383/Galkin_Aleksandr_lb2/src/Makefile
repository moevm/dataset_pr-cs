all: menu

menu: menu.o index_first_negative.o index_last_negative.o sum_between_negative.o sum_before_and_after_negative.o
	gcc menu.o index_first_negative.o index_last_negative.o sum_between_negative.o sum_before_and_after_negative.o -o menu

menu.o: menu.c index_first_negative.h index_last_negative.h sum_between_negative.h sum_before_and_after_negative.h
	gcc -std=c99 -c menu.c

index_first_negative.o: index_first_negative.c 
	gcc -std=c99 -c index_first_negative.c

index_last_negative.o: index_last_negative.c
	gcc -std=c99 -c index_last_negative.c

sum_between_negative.o: sum_between_negative.c index_first_negative.h index_last_negative.h
	gcc -std=c99 -c sum_between_negative.c

sum_before_and_after_negative.o: sum_before_and_after_negative.c index_first_negative.h index_last_negative.h
	gcc -std=c99 -c sum_before_and_after_negative.c

clean:
	rm -rf *.o *.h.gch menu
