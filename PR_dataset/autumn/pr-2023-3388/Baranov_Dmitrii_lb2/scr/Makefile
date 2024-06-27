all: menu.o max.o min.o diff.o sum.o Print.o
	gcc menu.o max.o min.o diff.o sum.o Print.o -o menu

menu.o: menu.c max.h min.h diff.h sum.h Print.h
	gcc -c -std=c99 menu.c

max.o: max.c max.h
	gcc -c -std=c99 max.c

min.o: min.c min.h
	gcc -c -std=c99 min.c

diff.o: diff.c max.h min.h diff.h
	gcc -c -std=c99 diff.c

sum.o: sum.c sum.h
	gcc -c -std=c99 sum.c

Print.o: Print.c Print.h
	gcc -c -std=c99 Print.c
	
clean:
	rm -f *.o menu: