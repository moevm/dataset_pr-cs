all: menu

menu: menu.o index_first_negative.o index_last_negative.o sum_between_negative.o sum_before_and_after_negative.o
	gcc -std=gnu99 -o menu menu.o index_first_negative.o index_last_negative.o sum_between_negative.o sum_before_and_after_negative.o

menu.o: menu.c
	gcc -std=gnu99 -c menu.c

index_first_negative.o: index_first_negative.c
	gcc -std=gnu99 -c index_first_negative.c

index_last_negative.o: index_last_negative.c
	gcc -std=gnu99 -c index_last_negative.c

sum_between_negative.o: sum_between_negative.c
	gcc -std=gnu99 -c sum_between_negative.c

sum_before_and_after_negative.o: sum_before_and_after_negative.c
	gcc -std=gnu99 -c sum_before_and_after_negative.c

clean:
	rm -rf *.o menu
