all: cw clean

cw: ioroutine.o sentence.o text.o processing.o menu.o cw.o
	gcc -g ioroutine.o sentence.o text.o processing.o menu.o cw.o -o cw

cw.o: cw.c ioroutine.h sentence.h text.h processing.h menu.h
	gcc -g -c cw.c

menu.o: menu.h menu.c
	gcc -g -c menu.c

processing.o: processing.h processing.c
	gcc -g -c processing.c

text.o: text.h text.c
	gcc -g -c text.c

ioroutine.o: ioroutine.h ioroutine.c
	gcc -g -c ioroutine.c

sentence.o: sentence.h sentence.c
	gcc -g -c sentence.c

clean:
	rm -rf *.o *.gch