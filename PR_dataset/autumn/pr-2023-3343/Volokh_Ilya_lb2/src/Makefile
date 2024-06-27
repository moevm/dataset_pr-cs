CSWHY := -std=gnu99
all: menu.o index_first_zero.o index_last_zero.o sum_between.o sum_before_and_after.o
	gcc $(CSWHY) -o menu menu.o index_first_zero.o index_last_zero.o sum_between.o sum_before_and_after.o

menu.o: menu.c
	gcc -c $(CSWHY) menu.c

index_first_zero.o: index_first_zero.c index_first_zero.h
	gcc -c $(CSWHY) index_first_zero.c

index_last_zero.o: index_last_zero.c index_last_zero.h
	gcc -c $(CSWHY) index_last_zero.c

sum_between.o: sum_between.c sum_between.h
	gcc -c $(CSWHY) sum_between.c

sum_before_and_after.o: sum_before_and_after.c sum_before_and_after.h
	gcc -c $(CSWHY) sum_before_and_after.c
clean:
	rm -f *.o menu
