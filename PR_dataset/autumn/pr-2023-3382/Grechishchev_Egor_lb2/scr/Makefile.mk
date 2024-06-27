all: menu.o sum.o diff.o abs_min.o index_1.o abs_max.o
	gcc menu.o sum.o diff.o abs_min.o index_1.o abs_max.o -o menu
menu.o: menu.c sum.h diff.h abs_min.h index_1.h abs_max.h 
	gcc -c -std=c99 menu.c
sum.o: sum.h sum.c index_1.h
	gcc -c -std=c99 sum.c
diff.o: diff.h diff.c abs_min.h abs_max.h
	gcc -c -std=c99 diff.c
abs_min.o: abs_min.h abs_min.c
	gcc -c -std=c99 abs_min.c
index_1.o: index_1.h index_1.c 
	gcc -c -std=c99 index_1.c
abs_max.o: abs_max.c abs_max.h 
	gcc -c -std=c99 abs_max.c
