all: menu.o max.o min.o diff.o sum.o
	gcc menu.o max.o min.o diff.o sum.o -o menu

menu.o: menu.c max.h min.h diff.h sum.h
	gcc -c -std=c99 menu.c

max.o: max.c max.h
	gcc -c -std=c99 max.c

min.o: min.c min.h
	gcc -c -std=c99 min.c

diff.o: diff.c diff.h max.h min.h
	gcc -c -std=c99 diff.c

sum.o: sum.c sum.h min.h
	gcc -c -std=c99 sum.c

clean:
	rm -rf *.o menu
