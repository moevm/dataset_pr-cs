all: cw
cw: main.o input_function.o free_memory_func.o text_processing_function.o functions.o
	gcc main.o input_function.o free_memory_func.o text_processing_function.o functions.o -o cw
	rm -rf *.o
main.o: main.c input_function.h free_memory_func.h text_processing_function.h functions.h 
	gcc -c main.c
input_function.o: input_function.c input_function.h functions.h free_memory_func.h 
	gcc -c input_function.c
text_processing_function.o: text_processing_function.c text_processing_function.h 
	gcc -c text_processing_function.c
free_memory_func.o: free_memory_func.c free_memory_func.h 
	gcc -c free_memory_func.c
functions.o: functions.c free_memory_func.h input_function.h 
	gcc -c functions.c
rebuild: clean cw

clean:
	rm -rf cw
	rm -rf *.o
