all: main.o get_data_input.o task_functions.o data_output.o
	gcc -std=c99 main.o get_data_input.o task_functions.o data_output.o -o cw
main.o: main.c get_data_input.h task_functions.h data_output.h
	gcc -c -std=c99 main.c
get_data_input.o: get_data_input.c data_output.h
	gcc -c -std=c99 get_data_input.c
task_functions.o: task_functions.c data_output.h
	gcc -c -std=c99 task_functions.c
data_output.o: data_output.c
	gcc -c -std=c99 data_output.c
