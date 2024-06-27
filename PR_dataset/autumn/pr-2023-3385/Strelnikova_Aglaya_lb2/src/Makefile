all: menu.o abs_max.o abs_min.o sum.o diff.o
	gcc menu.o abs_max.o abs_min.o sum.o diff.o -o menu
menu.o: menu.c abs_max.h abs_min.h diff.h sum.h
	gcc -c menu.c
abs_min.o: abs_min.c abs_min.h
	gcc -c abs_min.c
abs_max.o: diff.c diff.h abs_max.h
	gcc -c abs_max.c
diff.o: diff.c diff.h abs_max.h abs_min.h
	gcc -c diff.c
sum.o: sum.c sum.h
	gcc -c sum.c

