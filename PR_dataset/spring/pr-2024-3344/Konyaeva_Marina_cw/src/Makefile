all: main.o input.o functions.o
	gcc *.o -lpng -o cw -std=c99
main.o: main.c input.o functions.o checker.o *.h
	gcc -c -lpng main.c -std=c99
input.o: input.c 
	gcc -c -lpng input.c -std=c99
functions.o: functions.c 
	gcc -c -lpng functions.c -std=c99
checker.o: checker.c
	gcc -c -lpng checker.c -std=c99
clean:
	rm *.o cw
