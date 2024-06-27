all: cw.o input.o functions.o
		gcc *.o -o cw -std=c99
cw.o: cw.c input.o functions.o *.h
		gcc -c cw.c -std=c99
input.o: input.c 
		gcc -c input.c -std=c99
functions.o: functions.c 
		gcc -c functions.c -std=c99
clean:
		rm *.o cw