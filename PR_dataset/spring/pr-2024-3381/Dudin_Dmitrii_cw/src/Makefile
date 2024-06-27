all: main.o utils.o get_args.o check_args.o get_params.o io_img.o procces.o
	gcc -std=c99 main.o utils.o get_args.o check_args.o get_params.o io_img.o procces.o -o cw -lm

main.o: main.c utils.h get_args.h check_args.h structs.h defines.h io_img.h
	gcc -c main.c

utils.o: utils.c structs.h defines.h
	gcc -c utils.c

get_args.o: get_args.c utils.h structs.h defines.h
	gcc -c get_args.c

check_args.o: check_args.c utils.h structs.h defines.h
	gcc -c check_args.c

get_params.o: get_params.c utils.h structs.h defines.h
	gcc -c get_params.c

io_img.o: io_img.c structs.h defines.h utils.h
	gcc -c io_img.c

procces.o: procces.c structs.h defines.h utils.h
	gcc -c procces.c

clean:
	rm *.o cw

clean_bmp:
	rm *.bmp