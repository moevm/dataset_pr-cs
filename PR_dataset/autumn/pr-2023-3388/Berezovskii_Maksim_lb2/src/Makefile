all: menu.o abs_max.o abs_min.o diff.o sum.o key_func.o
	gcc -std=c99 menu.o abs_max.o abs_min.o diff.o sum.o key_func.o -o menu



menu.o: menu.c abs_max.h abs_min.h diff.h sum.h key_func.h
	gcc -c -std=c99 menu.c 

key_func.o: key_func.c key_func.h abs_max.h abs_min.h diff.h sum.h
	gcc -c -std=c99 key_func.c

abs_max.o: abs_max.c abs_max.h
	gcc -c -std=c99 abs_max.c

abs_min.o: abs_min.c abs_min.h
	gcc -c -std=c99 abs_min.c

diff.o: diff.c abs_max.h abs_min.h diff.h
	gcc -c -std=c99 diff.c

sum.o: sum.c abs_max.h sum.h
	gcc -c -std=c99 sum.c

clean:
	rm -f *.o menu