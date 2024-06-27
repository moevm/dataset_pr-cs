all: menu

menu: index_first_negative.o index_last_negative.o sum_between_negative.o sum_before_and_after_negative.o menu.o
	gcc menu.o index_first_negative.o index_last_negative.o sum_between_negative.o sum_before_and_after_negative.o -o menu

index_first_negative.o: index_first_negative.c index_first_negative.h
	gcc -c index_first_negative.c

index_last_negative.o: index_last_negative.c index_last_negative.h
	gcc -c index_last_negative.c

sum_between_negative.o: sum_between_negative.c sum_between_negative.h
	gcc -c sum_between_negative.c

sum_before_and_after_negative.o: sum_before_and_after_negative.c sum_before_and_after_negative.h
	gcc -c sum_before_and_after_negative.c

menu.o: menu.c
	gcc -c menu.c

clean:
	rm -rf *.o menu
