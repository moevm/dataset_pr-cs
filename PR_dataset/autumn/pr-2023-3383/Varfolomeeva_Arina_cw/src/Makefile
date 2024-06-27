all: main clean

main: main.o print_help.o read_t.o print_t.o free_t.o first_func.o second_func.o third_func.o fourth_func.o del_duplicates.o del_extra.o
	gcc main.o print_help.o read_t.o print_t.o free_t.o first_func.o second_func.o third_func.o fourth_func.o del_duplicates.o del_extra.o -o cw

main.o: main.c print_help.h read_t.h free_t.h first_func.h second_func.h third_func.h fourth_func.h del_duplicates.h

read_t.o: read_t.c struct.h
	gcc -c read_t.c

print_help.o: print_help.c struct.h
	gcc -c print_help.c

del_extra.o: del_extra.c struct.h
	gcc -c del_extra.c
	
del_duplicates.o: del_duplicates.c struct.h
	gcc -c del_duplicates.c

first_func.o: first_func.c struct.h
	gcc -c first_func.c

second_func.o: second_func.c struct.h
	gcc -c second_func.c
	
third_func.o: third_func.c struct.h
	gcc -c third_func.c
	
fourth_func.o: fourth_func.c struct.h
	gcc -c fourth_func.c

free_t.o: free_t.c struct.h
	gcc -c free_t.c

clean:
	rm -rf *.o main
	



