all: menu

menu: menu.o max.o min.o diff.o sum.o
	gcc menu.o max.o min.o diff.o sum.o -o menu

menu.o: menu.c
	gcc -c menu.c

max.o: max.c max.h
	gcc -c max.c
	
min.o: min.c min.h
	gcc -c min.c
	
diff.o: diff.c diff.h
	gcc -c diff.c
	
sum.o: sum.c sum.h
	gcc -c sum.c
	
clean:
	rm -rf *.o menu
