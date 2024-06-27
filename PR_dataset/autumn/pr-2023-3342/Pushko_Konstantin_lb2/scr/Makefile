all: menu.o max.o min.o diff.o sum.o input_data.o print_result.o
	gcc menu.o max.o min.o diff.o sum.o input_data.o print_result.o -o menu
menu.o: menu.c input_data.h print_result.h
	gcc -c menu.c
max.o: max.c max.h
	gcc -c max.c -std=c99
min.o: min.c min.h
	gcc -c min.c -std=c99
diff.o: diff.c diff.h max.h min.h
	gcc -c diff.c
sum.o: sum.c sum.h
	gcc -c sum.c -std=c99
input_data.o: input_data.h
	gcc -c input_data.c
print_result.o: print_result.h max.h min.h diff.h sum.h
	gcc -c print_result.c
