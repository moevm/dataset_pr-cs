menu: menu.o min.o max.o diff.o sum.o
	gcc menu.o min.o max.o diff.o sum.o -o menu
menu.o: menu.c sum.h min.h max.h diff.h
	gcc -c -std=c99 menu.c
min.o: min.c min.h
	gcc -c -std=c99 min.c
max.o: max.o max.h
	gcc -c -std=c99 max.c
diff.o: diff.c diff.h
	gcc -c -std=c99 diff.c
sum.o: sum.c sum.h
	gcc -c -std=c99 sum.c
clean:
	rm *.o menu
