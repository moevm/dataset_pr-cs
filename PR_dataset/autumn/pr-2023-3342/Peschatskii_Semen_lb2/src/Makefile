all: menu
menu: index_first_negative.o index_last_negative.o sum_between_negative.o sum_before_and_after_negative.o menu.o input.o output.o
	gcc index_first_negative.o index_last_negative.o sum_between_negative.o sum_before_and_after_negative.o input.o output.o menu.o -o menu
index_first_negative.o: index_first_negative.c
	gcc -c index_first_negative.c
index_last_negative.o: index_last_negative.c
	gcc -c index_last_negative.c
sum_between_negative.o: sum_between_negative.c
	gcc -c sum_between_negative.c
sum_before_and_after_negative.o: sum_before_and_after_negative.c
	gcc -c sum_before_and_after_negative.c
input.o: input.c
	gcc -c input.c
output.o: output.c
	gcc -c output.c
menu.o: menu.c
	gcc -c menu.c
clean:
	rm -rf *.o menu
