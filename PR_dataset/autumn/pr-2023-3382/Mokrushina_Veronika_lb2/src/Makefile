all: menu

menu: menu.o abs_max.o abs_min.o diff.o sum.o
	gcc menu.o abs_max.o abs_min.o diff.o sum.o -o menu

menu.o: menu.c abs_max.h abs_min.h diff.h sum.h
	gcc -c menu.c

abs_max.o: abs_max.h abs_max.c 
	gcc -c abs_max.c

abs_min.o: abs_min.h abs_min.c 
	gcc -c abs_min.c

diff.o: diff.h diff.c abs_min.h abs_max.h
	gcc -c diff.c

sum.o: sum.h sum.c abs_max.h
	gcc -c sum.c

