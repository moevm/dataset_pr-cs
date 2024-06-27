all: menu.o sum.o diff.o abs_max.o abs_min.o
	gcc -o menu menu.o sum.o diff.o abs_max.o abs_min.o
menu.o: menu.c
	gcc -c -std=c99 menu.c
sum.o: sum.c sum.h
	gcc -c -std=c99 sum.c
diff.o: diff.c diff.h
	gcc -c -std=c99 diff.c
abs_max.o: abs_max.c abs_max.h
	gcc -c -std=c99 abs_max.c
abs_min.o: abs_min.c abs_min.h
	gcc -c -std=c99 abs_min.c
clean:
	rm ./abs_max.o ./abs_min.o ./menu.o ./diff.o ./sum.o 