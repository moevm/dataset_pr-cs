main: main.o readtext.o functions_13.o free_memory.o print_text.o functions_24.o
	gcc main.o readtext.o functions_13.o free_memory.o print_text.o functions_24.o -o cw
main.o: main.c readtext.h functions_13.h free_memory.h print_text.h structs.h
	gcc -c main.c
readtext.o: readtext.c readtext.h structs.h
	gcc -c readtext.c
functions_13.o: functions_13.c functions_13.h structs.h
	gcc -c functions_13.c
free_memory.o: free_memory.c free_memory.h structs.h
	gcc -c free_memory.c
print_text.o: print_text.c print_text.h structs.h
	gcc -c print_text.c
functions_24.o: functions_24.c functions_24.h structs.h
	gcc -c functions_24.c
clean:
	rm -rf *.o main
