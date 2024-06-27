all: menu
	
menu: main.o min.o max.o diff.o sum.o
	gcc main.o  min.o max.o diff.o sum.o -o menu
	
min.o: min.c min.h
	gcc -c min.c -o min.o
	
max.o: max.c max.h
	gcc -c max.c -o max.o
	
diff.o: diff.c diff.h
	gcc -c diff.c -o diff.o
	
sum.o: sum.c sum.h
	gcc -c sum.c -o sum.o
	
main.o: menu.c menu.h
	gcc -c menu.c -o main.o
	
clean:
	rm -rf *.o menu	
	
	
