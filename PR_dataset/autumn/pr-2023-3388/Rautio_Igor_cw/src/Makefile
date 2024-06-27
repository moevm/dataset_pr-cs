all: cw clean

cw: utils.o str.o text.o menu.o cw.o
	gcc -g utils.o str.o text.o menu.o cw.o -o cw

utils.o: utils.h utils.c
	gcc -g -c utils.c

str.o: str.h str.c
	gcc -g -c str.c

text.o: text.h text.c
	gcc -g -c text.c

menu.o: menu.h menu.c
	gcc -g -c menu.c

cw.o: cw.c
	gcc -g -c cw.c

clean:
	rm *.o
