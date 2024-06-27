all: main.o input.o functions.o
	gcc *.o -o cw -std=c99
main.o: main.c input.o functions.o *.h
	gcc -c main.c -std=c99
input.o: input.c 
	gcc -c input.c -std=c99
functions.o: functions.c 
	gcc -c functions.c -std=c99
clean:
	rm *.o cw
