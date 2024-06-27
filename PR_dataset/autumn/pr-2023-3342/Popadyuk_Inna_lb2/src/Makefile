all: menu.o index_first_negative.o index_last_negative.o multi_between_negative.o multi_before_and_after_negative.o input.o output.o
	gcc menu.o index_first_negative.o index_last_negative.o multi_between_negative.o multi_before_and_after_negative.o input.o output.o -o menu

menu.o: menu.c 
	gcc -c -std=c99  menu.c

input.o: input.c input.h
	gcc -c -std=c99 input.c

output.o: output.c output.h index_first_negative.h index_last_negative.h multi_between_negative.h multi_before_and_after_negative.h
	gcc -c -std=c99 output.c

index_first_negative.o: index_first_negative.c index_first_negative.h
	gcc -c -std=c99   index_first_negative.c

index_last_negative.o: index_last_negative.c index_last_negative.h
	gcc -c -std=c99  index_last_negative.c

multi_between_negative.o: multi_between_negative.c index_last_negative.h index_first_negative.h multi_between_negative.h
	gcc -c -std=c99  multi_between_negative.c

multi_before_and_after_negative.o: multi_before_and_after_negative.c index_last_negative.h index_first_negative.h multi_before_and_after_negative.h
	gcc -c -std=c99  multi_before_and_after_negative.c
