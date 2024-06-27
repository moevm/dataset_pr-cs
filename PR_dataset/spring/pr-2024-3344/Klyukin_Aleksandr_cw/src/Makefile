all: main.o files_action.o actions.o input_hell.o checkers.o
	gcc  main.o files_action.o actions.o input_hell.o checkers.o -o cw -lm

main.o: main.c
	gcc -c main.c
files_action.o: files_action.c files_action.h
	gcc -c files_action.c
actions.o: actions.c actions.h
	gcc -c actions.c
input_hell.o: input_hell.c input_hell.h
	gcc -c input_hell.c
checkers.o: checkers.c checkers.h
	gcc -c  checkers.c
clean:
	rm *.o