all: menu.o max.o min.o diff.o sum.o 
	gcc menu.o max.o min.o diff.o sum.o -o menu
menu.o: menu.c max.h min.h diff.h sum.h
	gcc -std=c99 -c menu.c 
max.o: max.c max.h
	gcc -std=c99 -c max.c 
min.o: min.c min.h
	gcc -std=c99 -c min.c
diff.o: diff.c max.h min.h diff.h
	gcc -std=c99 -c diff.c
sum.o: sum.c min.h sum.h
	gcc -std=c99 -c sum.c
