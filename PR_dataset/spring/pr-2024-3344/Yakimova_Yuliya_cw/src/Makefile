all: main.o input.o functions.o
	gcc *.o -lpng -lm -o cw -std=c99
main.o: main.c input.o functions.o *.h
	gcc -c -lpng -lm main.c -std=c99
input.o: input.c input.h library.h structures.h
	gcc -c -lpng -lm input.c -std=c99
functions.o: functions.c *.h
	gcc -c -lpng -lm functions.c -std=c99
clean:
	rm *.o cw