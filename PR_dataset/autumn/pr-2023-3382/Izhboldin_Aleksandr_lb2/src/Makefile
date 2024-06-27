TARGET = menu
ARGS = -std=c99
CC = gcc

$(TARGET) : index_first_even.o index_last_odd.o sum_between_even_odd.o sum_before_even_and_after_odd.o menu.o 
	$(CC) $(ARGS) menu.o index_first_even.o index_last_odd.o sum_between_even_odd.o sum_before_even_and_after_odd.o -o $(TARGET)

index_first_even.o : index_first_even.h index_first_even.c
	$(CC) $(ARGS) -c index_first_even.c -o index_first_even.o

index_last_odd.o : index_last_odd.h index_last_odd.c
	$(CC) $(ARGS) -c index_last_odd.c -o index_last_odd.o

sum_between_even_odd.o : sum_between_even_odd.h sum_between_even_odd.c
	$(CC) $(ARGS) -c sum_between_even_odd.c -o sum_between_even_odd.o

sum_before_even_and_after_odd.o : sum_before_even_and_after_odd.h sum_before_even_and_after_odd.c
	$(CC) $(ARGS) -c sum_before_even_and_after_odd.c -o sum_before_even_and_after_odd.o

menu.o : menu.c
	$(CC) $(ARGS) -c menu.c -o menu.o

clean:
	rm *.o $(TARGET)
