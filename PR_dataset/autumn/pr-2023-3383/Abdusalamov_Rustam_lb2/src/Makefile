all: menu

menu: menu.o index_first_negative.o index_last_negative.o multi_between_negative.o multi_before_and_after_negative.o
	gcc menu.o index_first_negative.o index_last_negative.o multi_between_negative.o multi_before_and_after_negative.o -o menu
menu.o: menu.c
	gcc -c menu.c -std=c99
index_first_negative.o: index_first_negative.c
	gcc -c index_first_negative.c -std=c99
index_last_negative.o: index_last_negative.c
	gcc -c index_last_negative.c -std=c99
multi_between_negative.o: multi_between_negative.c
	gcc -c multi_between_negative.c -std=c99
multi_before_and_after_negative.o: multi_before_and_after_negative.c
	gcc -c multi_before_and_after_negative.c -std=c99
clean:
	rm *.o menu
