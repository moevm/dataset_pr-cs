all: menu.o abs_max.o abs_min.o diff.o sum.o input.o output.o
	gcc menu.o abs_max.o abs_min.o diff.o sum.o input.o output.o -o menu
menu.o: menu.c
	gcc -c menu.c
abs_max.o: abs_max.c abs_max.h
	gcc -c abs_max.c
abs_min.o: abs_min.c abs_min.h
	gcc -c abs_min.c
diff.o: diff.c diff.h
	gcc -c diff.c
sum.o: sum.c sum.h
	gcc -c sum.c
input.o: input.c input.h
	gcc -c input.c
output.o: output.c output.h
	gcc -c output.c
clean:
	rm -rf *.o menu