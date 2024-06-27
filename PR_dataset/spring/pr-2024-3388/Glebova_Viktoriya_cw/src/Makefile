all: main.o utils.o args.o get_params.o io_img.o change_img.o
	gcc -std=c99 main.o utils.o args.o get_params.o io_img.o change_img.o -o cw -lpng -lm

main.o: main.c utils.h args.h structs.h defines.h
	gcc -c main.c

utils.o: utils.c structs.h defines.h
	gcc -c utils.c

args.o: args.c utils.h structs.h defines.h
	gcc -c args.c

get_params.o: get_params.c utils.h structs.h defines.h
	gcc -c get_params.c

io_img.o: io_img.c structs.h structs.h defines.h utils.h
	gcc -c io_img.c

process_img.o: change_img.c utils.h structs.h defines.h structs.h
	gcc -c change_img.c

clean:
	rm *.o cw