all: menu.o abs_max.o abs_min.o diff.o sum.o fill_arr.o answer.o
	gcc menu.c abs_max.c abs_min.c diff.c sum.c fill_arr.c answer.c -o menu -std=c99

menu.o: menu.c
	gcc -c menu.c -std=c99

abs_max.o: abs_max.c
	gcc -c abs_max.c -std=c99

abs_min.o: abs_min.c
	gcc -c abs_min.c -std=c99

diff.o: diff.c
	gcc -c diff.c -std=c99

sum.o: sum.c 
	gcc -c sum.c -std=c99

fill_arr.o: fill_arr.c
	gcc -c fill_arr.c -std=c99

answer.o: answer.c
	gcc -c answer.c -std=c99

clean:
	rm -rf *.o
