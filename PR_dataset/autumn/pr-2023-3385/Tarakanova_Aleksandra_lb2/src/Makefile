all: menu
menu: main.o index_first_negative.o index_last_negative.o sum_between_negative.o sum_before_and_after_negative.o
	gcc main.o  index_first_negative.o index_last_negative.o sum_between_negative.o sum_before_and_after_negative.o -o menu
index_first_negative.o: index_first_negative.c index_first_negative.h
	gcc -c index_first_negative.c -o index_first_negative.o
index_last_negative.o: index_last_negative.c index_last_negative.h
	gcc -c index_last_negative.c -o index_last_negative.o
sum_between_negative.o: sum_between_negative.c sum_between_negative.h
	gcc -c sum_between_negative.c -o sum_between_negative.o
sum_before_and_after_negative.o: sum_before_and_after_negative.c sum_before_and_after_negative.h
	gcc -c sum_before_and_after_negative.c -o sum_before_and_after_negative.o
main.o: menu.c menu.h 
	gcc -c menu.c -o main.o
clean:
	rm -rf *.o menu	
