all: menu.o max.o min.o diff.o sum.o get_result.o  input_arr.o
	gcc menu.o max.o min.o diff.o sum.o get_result.o input_arr.o -o menu -std=c99
menu.o: menu.c get_result.h
	gcc -c menu.c -std=c99
max.o: max.c max.h
	gcc -c max.c -std=c99
min.o: min.h min.c
	gcc -c min.c -std=c99
diff.o: diff.h diff.c max.h min.h
	gcc -c diff.c -std=c99
sum.o: sum.h sum.c min.h
	gcc -c sum.c -std=c99
get_result.o: get_result.h get_result.c min.h max.h diff.h sum.h 
	gcc -c get_result.c -std=c99
input_arr.o: input_arr.c input_arr.h 
	gcc -c input_arr.c -std=c99
clean:
	rm -rf *.o	
