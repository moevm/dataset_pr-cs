all: main.o actions.o input_output.o
	gcc main.o actions.o input_output.o -o cw

main.o: main.c actions.h input_output.h
	gcc -c main.c

actions.o: actions.c actions.h input_output.h
	gcc -c actions.c

input_output.o: input_output.c input_output.h
	gcc -c input_output.c
