TARGET = menu
CC = gcc

$(TARGET) : menu.o index_first_zero.o index_last_zero.o sum_before_and_after.o sum_between.o
	$(CC) menu.o index_first_zero.o index_last_zero.o sum_before_and_after.o sum_between.o -o $(TARGET)

menu.o : menu.c index_first_zero.h index_last_zero.h sum_before_and_after.h sum_between.h
	$(CC) -c menu.c -o menu.o 

index_first_zero.o : index_first_zero.c index_first_zero.h
	$(CC) -c index_first_zero.c -o index_first_zero.o

index_last_zero.o : index_last_zero.c index_last_zero.h
	$(CC) -c index_last_zero.c -o index_last_zero.o

sum_before_and_after.o : sum_before_and_after.c sum_before_and_after.h
	$(CC) -c sum_before_and_after.c -o sum_before_and_after.o

sum_between.o : sum_between.c sum_between.h
	$(CC) -c sum_between.c -o sum_between.o

clean : 
	rm $(TARGET) *.o