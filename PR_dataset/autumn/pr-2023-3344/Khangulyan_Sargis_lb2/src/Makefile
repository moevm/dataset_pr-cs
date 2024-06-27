all: menu.o abs_max.o abs_min.o diff.o sum.o
    gcc menu.o abs_max.o abs_min.o diff.o sum.o -o menu -std=c99

menu.o: menu.c abs_max.h abs_min.h diff.h sum.h
    gcc -c menu.c -std=c99

abs_max.o: abs_max.c
    gcc -c abs_max.c -std=c99

abs_min.o: abs_min.c
    gcc -c abs_min.c -std=c99

diff.o: diff.c abs_max.h abs_min.h
    gcc -c diff.c -std=c99

sum.o: sum.c abs_max.h
    gcc -c sum.c -std=c99

clean:
    rm *.o