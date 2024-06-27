all: menu.o
	gcc -o menu *.o -std=c99

menu.o: *.c
	gcc -c *.c -std=c99

max.o: max.h max.c
	gcc -c max.c -std=c99

min.o: max.h min.c
	gcc -c min.c -std=c99

diff.o: max.h min.h diff.h diff.c
	gcc -c diff.c -std=c99

sum.o:  min.h sum.h sum.c
	gcc -c sum.c -std=c99

clean:
	rm *.o