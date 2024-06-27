all: menu.o input_key.o input_arr.o max.o min.o sum.o diff.o choice.o
	gcc menu.o input_key.o input_arr.o max.o min.o sum.o diff.o choice.o -o menu
menu.o: menu.c input_key.h input_arr.h choice.h
	gcc -c menu.c
input_key.o: input_key.c input_key.h
	gcc -c input_key.c
input_arr.o: input_arr.c input_arr.h
	gcc -c input_arr.c
max.o: max.c max.h
	gcc -c -std=c99 max.c
min.o: min.c min.h
	gcc -c -std=c99 min.c
sum.o: sum.c sum.h min.h
	gcc -c -std=c99 sum.c
diff.o: diff.c diff.h max.h min.h
	gcc -c -std=c99 diff.c
choice.o: choice.c choice.h max.h min.h sum.h diff.h
	gcc -c choice.c
clean:
	rm -rf *.o menu
