all: main.o get_args.o help_functions.o read_picture.o change_picture.o
	gcc -std=c99 main.o get_args.o help_functions.o read_picture.o change_picture.o -o cw

main.o: main.c get_args.h defines.h structs.h read_picture.h change_picture.h
	gcc -c main.c

get_args.o: get_args.c get_args.h defines.h structs.h help_functions.h
	gcc -c get_args.c

help_functions.o: help_functions.h defines.h structs.h
	gcc -c help_functions.c

read_picture.o: read_picture.c read_picture.h structs.h defines.h help_functions.h
	gcc -c read_picture.c

change_picture.o: change_picture.c structs.h help_functions.h 
	gcc -c change_picture.c

clean:
	rm -rf *.o