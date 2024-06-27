all: cw

cw: main.o function_1.o function_2.o function_3.o function_9.o help_functions.o input_functions.o input_processing.o
	gcc -g main.o function_1.o function_2.o function_3.o function_9.o help_functions.o input_functions.o input_processing.o -o cw

main.o: main.c
	gcc -c -g main.c -o main.o

function_1.o: function_1.c function_1.h 
	gcc -c -g function_1.c -o function_1.o

function_2.o: function_2.c function_2.h 
	gcc -c -g function_2.c -o function_2.o 

function_3.o: function_3.c function_3.h 
	gcc -c -g function_3.c -o function_3.o

function_9.o: function_9.c function_9.h 
	gcc -c -g function_9.c -o function_9.o

help_functions.o: help_functions.c help_functions.h
	gcc -c -g help_functions.c -o help_functions.o

input_functions.o: input_functions.c input_functions.h
	gcc -c -g input_functions.c -o input_functions.o

input_processing.o: input_processing.c input_processing.h
	gcc -c -g input_processing.c -o input_processing.o

make clean:
	rm *.o cw