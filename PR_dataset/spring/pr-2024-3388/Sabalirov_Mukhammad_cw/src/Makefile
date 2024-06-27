all: main.o validate.o args.o utils.o params.o io.o process.o
	gcc -std=c99 main.o validate.o args.o utils.o params.o io.o process.o -o cw -lpng -lm

main.o: main.c args.h utils.h io.h
	gcc -c main.c
	
validate.o: validate.c consts.h structs.h utils.h
	gcc -c validate.c

params.o: params.c consts.h structs.h utils.h args.h
	gcc -c params.c

args.o: args.c consts.h structs.h validate.h utils.h
	gcc -c args.c

utils.o: utils.c consts.h
	gcc -c utils.c

io.o: io.c utils.h consts.h structs.h
	gcc -c io.c

process.o: process.c utils.h consts.h structs.h
	gcc -c process.c

clean:
	rm *.o *.png cw