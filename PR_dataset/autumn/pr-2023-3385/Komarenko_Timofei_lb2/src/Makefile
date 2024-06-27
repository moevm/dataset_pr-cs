all: menu

menu: menu.o abs_max.o abs_min.o diff.o sum.o
	gcc menu.o abs_max.o abs_min.o diff.o sum.o -o menu
abs_max.o: abs_max.c abs_max.h
	gcc -c -std=gnu99 abs_max.c -o abs_max.o
abs_min.o: abs_min.c abs_min.h
	gcc -c -std=gnu99 abs_min.c -o abs_min.o
diff.o: diff.c diff.h
	gcc -c -std=gnu99 diff.c -o diff.o
sum.o: sum.c sum.h
	gcc -c -std=gnu99 sum.c -o sum.o
menu.o: menu.c 
	gcc -c -std=gnu99 menu.c -o menu.o
clear:
	rm -rf *.o menu
