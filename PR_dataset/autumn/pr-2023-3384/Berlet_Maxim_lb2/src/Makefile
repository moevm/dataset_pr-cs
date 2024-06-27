all: menu.o choose_option.o arr_input.o max.o min.o diff.o sum.o
	gcc menu.o choose_option.o arr_input.o max.o min.o diff.o sum.o -o menu
menu.o: menu.c
	gcc -c menu.c
choose_option.o: choose_option.c choose_option.h
	gcc -c choose_option.c
arr_input.o: arr_input.c arr_input.h
	gcc -c arr_input.c
max.o: max.c max.h
	gcc -c max.c
min.o: min.c min.h
	gcc -c min.c
diff.o: diff.c diff.h
	gcc -c diff.c
sum.o: sum.c sum.h
	gcc -c sum.c
