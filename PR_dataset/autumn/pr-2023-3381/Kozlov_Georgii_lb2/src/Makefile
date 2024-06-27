all: menu.o max.o max.h min.o min.h diff.h diff.o sum.h sum.o
        gcc menu.o max.o min.o diff.o sum.o -o menu -std=gnu99
menu.o: menu.c  max.h min.h diff.h sum.h
        gcc -c menu.c -std=gnu99
max.o: max.c
        gcc -c max.c -std=gnu99
min.o: min.c
        gcc -c min.c -std=gnu99
diff.o: diff.c max.h min.h
        gcc -c diff.c -std=gnu99
sum.o: sum.c min.h
        gcc -c sum.c -std=gnu99
