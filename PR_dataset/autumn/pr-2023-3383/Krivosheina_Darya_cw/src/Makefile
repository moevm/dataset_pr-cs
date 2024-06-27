all: main clean
main: main.o read.o date.o reverse.o delete.o sort.o search_word.o free_all.o 
	gcc main.o read.o date.o reverse.o delete.o sort.o search_word.o free_all.o -o cw
main.o: main.c read.h struct.h date.h reverse.h delete.h free_all.h sort.h search_word.h
	gcc -std=c99 -c main.c 
read.o: read.c read.h struct.h
	gcc -std=c99 -c read.c
date.o: date.c date.h struct.h
	gcc -std=c99 -c date.c
reverse.o: reverse.c reverse.h struct.h 
	gcc -std=c99 -c reverse.c
delete.o: delete.c delete.h struct.h
	gcc -std=c99 -c delete.c
sort.o: sort.c sort.h struct.h
	gcc -std=c99 -c sort.c
search_word.o: search_word.c search_word.h struct.h
	gcc -std=c99 -c search_word.c
free_all.o: free_all.c free_all.h struct.h
	gcc -std=c99 -c free_all.c
clean: 
	rm -rf *.o main
