all: menu.o abs_max.o abs_min.o diff.o sum.o input.o output.o
	gcc menu.o abs_max.o abs_min.o diff.o sum.o input.o output.o -o menu

menu.o: menu.c input.h output.h
	gcc -c menu.c

abs_max.o: abs_max.c abs_max.h
	gcc -c abs_max.c -std=c99

abs_min.o: abs_min.c abs_min.h
	gcc -c abs_min.c -std=c99

diff.o: diff.c diff.h abs_max.h abs_min.h
	gcc -c diff.c

sum.o: sum.c sum.h abs_max.h
	gcc -c sum.c -std=c99

input.o: input.c input.h
	gcc -c input.c -std=c99

output.o: output.c output.h abs_max.h abs_min.h diff.h sum.h
	gcc -c output.c -std=c99