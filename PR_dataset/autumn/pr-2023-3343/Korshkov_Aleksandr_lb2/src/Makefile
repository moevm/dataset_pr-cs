all: menu.o index_first_negative.o index_last_negative.o multi_before_and_after_negative.o multi_between_negative.o
	gcc menu.o index_first_negative.o index_last_negative.o multi_before_and_after_negative.o multi_between_negative.o -o menu -std=gnu99

menu.o: menu.c multi_before_and_after_negative.h multi_between_negative.h index_first_negative.h index_last_negative.h
	gcc -c menu.c -std=gnu99

index_first_negative.o: index_first_negative.c index_first_negative.h
	gcc -c index_first_negative.c -std=gnu99

index_last_negative.o: index_last_negative.c index_last_negative.h
	gcc -c index_last_negative.c -std=gnu99

multi_before_and_after_negative.o: multi_before_and_after_negative.c multi_before_and_after_negative.h index_first_negative.h index_last_negative.h
	gcc -c multi_before_and_after_negative.c -std=gnu99

multi_between_negative.o: multi_between_negative.c multi_between_negative.h index_first_negative.h index_last_negative.h
	gcc -c multi_between_negative.c -std=gnu99

clean:
	rm menu.o index_first_negative.o index_last_negative.o multi_before_and_after_negative.o multi_between_negative.o menu
