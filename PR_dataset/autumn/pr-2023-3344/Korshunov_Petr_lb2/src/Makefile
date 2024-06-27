all: menu.o max.o min.o diff.o sum.o
	gcc menu.o max.o min.o diff.o sum.o -o menu -std=c99

menu.o: menu.c max.h min.h diff.h sum.h
	gcc -c menu.c -std=c99

max.o: max.c
	gcc -c max.c -std=c99

min.o: min.c
	gcc -c min.c -std=c99

diff.o: diff.c max.h min.h
	gcc -c diff.c -std=c99

sum.o: sum.c min.h
	gcc -c sum.c -std=c99

clean:
	rm *.o