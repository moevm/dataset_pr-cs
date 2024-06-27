all: menu.o abs_max.o abs_min.o diff.o sum.o input.o output.o
	gcc menu.o abs_max.o abs_min.o diff.o sum.o input.o output.o -o menu

menu.o: menu.c
	gcc -c menu.c

abs_max.o: abs_max.c abs_max.h
	gcc -c -std=c99 abs_max.c

abs_min.o: abs_min.c abs_min.h
	gcc -c -std=c99 abs_min.c

diff.o: diff.c diff.h
	gcc -c -std=c99 diff.c

sum.o: sum.c sum.h
	gcc -c -std=c99 sum.c

input.o: input.c input.h
	gcc -c -std=c99 sum.c

output.o: output.c output.h
	gcc -c -std=c99 sum.c

