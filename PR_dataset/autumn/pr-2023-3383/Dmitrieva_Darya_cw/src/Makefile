all: main clean 
 
main: main.o first_function.o ninth_function.o second_function.o third_function.o fourth_function.o Free.o Print.o Preprocessing.o 
	gcc main.o first_function.o ninth_function.o second_function.o third_function.o fourth_function.o Free.o Print.o Preprocessing.o -o cw 
 
main.o: main.c first_function.o ninth_function.o second_function.o third_function.o fourth_function.o Free.o Print.o Preprocessing.o structs.h 
 
first_function.o: first_function.c structs.h 
	gcc -c first_function.c 
 
second_function.o: second_function.c structs.h 
	gcc -c second_function.c 
 
third_function.o: third_function.c structs.h 
	gcc -c third_function.c 
 
fourth_function.o: fourth_function.c structs.h 
	gcc -c fourth_function.c 
 
Free.o: Free.c structs.h 
	gcc -c Free.c 
 
Print.o: Print.c structs.h 
	gcc -c Print.c 

Preprocessing.o: Preprocessing.c structs.h 
	gcc -c Preprocessing.c 
  
ninth_function.o: ninth_function.c structs.h
	gcc -c ninth_function.c 
clean: 
	rm -rf *.o main
