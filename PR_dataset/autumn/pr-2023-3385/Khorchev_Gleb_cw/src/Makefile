all: cw

cw: main.o func_1.o func_2.o func_4.o func_9.o input_functions.o help_functions.o
	gcc main.o func_1.o func_2.o func_4.o func_9.o input_functions.o help_functions.o -o cw

main.o: main.c struct.h input_functions.h help_functions.h func_1.h func_2.h func_4.h
	gcc -g -c main.c

input_functions.o: input_functions.c input_functions.h struct.h help_functions.h
	gcc -g -c input_functions.c

help_functions.o: help_functions.c help_functions.h struct.h
	gcc -g -c help_functions.c

func_1.o: func_1.c func_1.h struct.h help_functions.h
	gcc -g -c func_1.c

func_2.o: func_2.c func_2.h struct.h
	gcc -g -c func_2.c

func_4.o: func_4.c func_4.h struct.h help_functions.h
	gcc -g -c func_4.c

func_9.o: func_9.c func_9.h struct.h
	gcc -g -c func_9.c

clean:
	rm -rf *.o cw
