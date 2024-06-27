all: menu.o abs_max.o abs_min.o diff.o sum.o 
	gcc -std=c99 menu.o abs_max.o abs_min.o diff.o sum.o -o menu

menu.o: menu.c
	gcc -c -std=c99 menu.c

abs_max.o: abs_max.c
	gcc -c -std=c99 abs_max.c

abs_min.o: abs_min.c
	gcc -c -std=c99 abs_min.c

diff.o: diff.c
	gcc -c -std=c99 diff.c

sum.o: sum.c
	gcc -c -std=c99 sum.c

clean:
	rm -rf *.o