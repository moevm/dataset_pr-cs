CC = gcc

.PHONY: all clean

all : menu.o min.o max.o diff.o sum.o
	$(CC) menu.o min.o max.o diff.o sum.o -o menu
    
menu.o: menu.c min.h max.h diff.h sum.h
	$(CC) -c menu.c

min.o: min.c min.h
	$(CC) -c min.c 
    
max.o: max.c max.h
	$(CC) -c max.c
    
diff.o: diff.c diff.h min.h max.h
	$(CC) -c diff.c
    
sum.o: sum.c sum.h min.h
	$(CC) -c sum.c

clean:
 	rm -f *.o
