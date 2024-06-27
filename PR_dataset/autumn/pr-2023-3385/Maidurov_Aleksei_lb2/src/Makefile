all: menu

menu: menu.o diff.o max.o min.o sum.o
	gcc menu.o diff.o max.o min.o sum.o -o menu -std=c99

menu.o: menu.c diff.h max.h min.h sum.h
	gcc menu.c -c -std=c99

diff.o: diff.c max.h min.h
	gcc diff.c -c -std=c99

max.o: max.c
	gcc max.c -c -std=c99

min.o: min.c
	gcc min.c -c -std=c99

sum.o: sum.c min.h
	gcc sum.c -c -std=c99

clean:
	rm -rf menu *.o
