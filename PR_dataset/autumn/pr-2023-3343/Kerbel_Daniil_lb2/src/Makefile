CSWHY := -std=gnu99
all: menu.o index_first_negative.o index_last_negative.o sum_between_negative.o sum_before_and_after_negative.o
	gcc $(CSWHY) -o menu menu.o index_first_negative.o index_last_negative.o sum_between_negative.o sum_before_and_after_negative.o

menu.o: menu.c
	gcc -c $(CSWHY) menu.c

index_first_negative.o: index_first_negative.c index_first_negative.h
	gcc -c $(CSWHY) index_first_negative.c

index_last_negative.o: index_last_negative.c index_last_negative.h
	gcc -c $(CSWHY) index_last_negative.c

sum_between_negative.o: sum_between_negative.c sum_between_negative.h
	gcc -c $(CSWHY) sum_between_negative.c

sum_before_and_after_negative.o: sum_before_and_after_negative.c sum_before_and_after_negative.h
	gcc -c $(CSWHY) sum_before_and_after_negative.c
clean:
	rm -f *.o menu
