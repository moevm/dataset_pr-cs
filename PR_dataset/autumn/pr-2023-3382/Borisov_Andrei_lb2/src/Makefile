all: menu.o max.o min.o sum.o diff.o
	gcc menu.o max.o min.o sum.o diff.o -o menu -std=c99

menu.o: menu.c max.h min.h sum.h diff.h
	gcc -c menu.c -std=c99

max.o: max.c max.h
	gcc -c max.c -std=c99

min.o: min.c min.h
	gcc -c min.c -std=c99

sum.o: sum.c sum.h min.h
	gcc -c sum.c -std=c99

diff.o: diff.c diff.h min.h max.h
	gcc -c diff.c -std=c99

clean:
	rm -f *.o menu