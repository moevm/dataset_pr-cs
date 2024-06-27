all: menu.o
	gcc max.o min.o diff.o sum.o menu.o -o menu
menu.o: menu.c max.o min.o diff.o sum.o
	gcc -c menu.c -std=c99
max.o: max.c
	gcc -c max.c -std=c99
min.o: min.c
	gcc -c min.c -std=c99
sum.o: sum.c min.o
	gcc -c sum.c -std=c99
diff.o: diff.c min.o max.o
	gcc -c diff.c -std=c99