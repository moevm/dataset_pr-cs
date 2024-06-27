all: menu.o index_first_negative.o index_last_negative.o multi_before_and_after_negative.o multi_between_negative.o
	gcc -std=gnu99 menu.o index_first_negative.o index_last_negative.o multi_before_and_after_negative.o multi_between_negative.o -o menu

menu.o: menu.c index_first_negative.h index_last_negative.h multi_before_and_after_negative.h multi_between_negative.h
	gcc -std=gnu99 -c menu.c

index_first_negative.o: index_first_negative.c
	gcc -std=gnu99 -c index_first_negative.c

index_last_negative.o: index_last_negative.c
	gcc -std=gnu99 -c index_last_negative.c

multi_before_and_after_negative.o: multi_before_and_after_negative.c index_first_negative.h index_last_negative.h
	gcc -std=gnu99 -c multi_before_and_after_negative.c

multi_between_negative.o: multi_between_negative.c
	gcc -std=gnu99 -c multi_between_negative.c