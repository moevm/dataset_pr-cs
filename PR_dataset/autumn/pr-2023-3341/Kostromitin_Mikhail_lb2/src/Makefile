all: menu.o input.o output.o index_first_negative.o index_last_negative.o sum_between_negative.o sum_before_and_after_negative.o
	gcc menu.o input.o output.o index_first_negative.o index_last_negative.o sum_between_negative.o sum_before_and_after_negative.o -o menu
menu.o: menu.c input.c output.c
	gcc -c menu.c
input.o: input.c
	gcc -c input.c
output.o: output.c index_first_negative.c index_last_negative.c sum_between_negative.c sum_before_and_after_negative.c
	gcc -c output.c
index_first_negative.o: index_first_negative.c
	gcc -c -std=gnu99 index_first_negative.c
index_last_negative.o: index_last_negative.c
	gcc -c -std=gnu99 index_last_negative.c
sum_between_negative.o: index_first_negative.c index_last_negative.c sum_between_negative.c
	gcc -c -std=gnu99 sum_between_negative.c
sum_before_and_after_negative.o: index_first_negative.c index_last_negative.c sum_before_and_after_negative.c
	gcc -c -std=gnu99 sum_before_and_after_negative.c
clean:
	rm -rf *.o menu
