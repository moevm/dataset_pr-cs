all: main clean
main: main.o freedom.o printer.o sort.o zero_changer.o up_changer.o vowels_sort.o input.o similar.o model.o
	gcc main.o freedom.o printer.o sort.o zero_changer.o up_changer.o vowels_sort.o input.o similar.o model.o -o cw
main.o: main.c freedom.h printer.h sort.h zero_changer.h up_changer.h vowels_sort.h input.h similar.h model.h
	gcc -c -g main.c 
printer.o: printer.c struct.h
	gcc -c -g printer.c 
freedom.o: freedom.c struct.h
	gcc -c -g freedom.c
sort.o: sort.c struct.h
	gcc -c -g sort.c
vowels_sort.o: vowels_sort.c sort.h struct.h 
	gcc -c -g vowels_sort.c
similar.o: similar.c struct.h
	gcc -c -g similar.c
model.o: model.c sort.h struct.h
	gcc -c -g model.c
zero_changer.o: zero_changer.c struct.h
	gcc -c -g zero_changer.c
input.o: input.c struct.h
	gcc -c -g input.c
up_changer.o: up_changer.c struct.h
	gcc -c -g up_changer.c

clean: 
	rm -rf *.o 
