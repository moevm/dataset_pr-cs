all: menu.o index_first_negative.o index_last_negative.o multi_between_negative.o multi_before_and_after_negative.o
	gcc menu.o index_first_negative.o index_last_negative.o multi_between_negative.o multi_before_and_after_negative.o -o menu
menu.o: menu.c index_first_negative.h index_last_negative.h multi_between_negative.h multi_before_and_after_negative.h
	gcc -c -std=c99 menu.c
index_first_negative.o: index_first_negative.c index_first_negative.h index_last_negative.h multi_between_negative.h multi_before_and_after_negative.h
	gcc -c -std=c99 index_first_negative.c
index_last_negative.o: index_last_negative.c index_first_negative.h index_last_negative.h multi_between_negative.h multi_before_and_after_negative.h
	gcc -c -std=c99 index_last_negative.c
multi_between_negative.o: multi_between_negative.c index_first_negative.h index_last_negative.h multi_between_negative.h multi_before_and_after_negative.h
	gcc -c -std=c99 multi_between_negative.c
multi_before_and_after_negative.o: multi_before_and_after_negative.c index_first_negative.h index_last_negative.h multi_between_negative.h multi_before_and_after_negative.h
	gcc -c -std=c99 multi_before_and_after_negative.c
clean:
	rm -f *.o menu