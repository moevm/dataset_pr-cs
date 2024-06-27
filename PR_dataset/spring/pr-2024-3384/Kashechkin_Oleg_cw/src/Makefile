TARGET = cw
CC = gcc

$(TARGET) : cw.o command.o image.o utils.o 
	$(CC) cw.o command.o image.o utils.o -o $(TARGET) -lpng -lm

cw.o : cw.c main.h command.h image.h utils.h 
	$(CC) -c cw.c -o cw.o 

command.o : command.c command.h main.h
	$(CC) -c command.c -o command.o

image.o : image.c image.h main.h
	$(CC) -c image.c -o image.o

utils.o : utils.c utils.h main.h
	$(CC) -c utils.c -o utils.o

clean : 
	rm $(TARGET) *.o