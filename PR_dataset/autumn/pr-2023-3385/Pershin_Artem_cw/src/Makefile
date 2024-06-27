all: do
do:  main.o InOut.o subfunctions.o functions.o free.o
	gcc main.o InOut.o free.o functions.o subfunctions.o -o cw
main.o: main.c structs.h free.h InOut.h functions.h
	gcc -c main.c
InOut.o: InOut.c InOut.h structs.h
	gcc -c InOut.c
free.o: free.c free.h structs.h
	gcc -c free.c
subfunctions.o: subfunctions.c subfunctions.h structs.h
	gcc -c subfunctions.c
functions.o: subfunctions.h functions.c functions.h structs.h free.h
	gcc -c functions.c
clean:
	rm -rf *.o cw
