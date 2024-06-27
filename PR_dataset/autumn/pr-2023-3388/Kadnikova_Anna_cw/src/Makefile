all: cw clean

cw: console.o sentence.o text.o stringswork.o menu.o cw.o
	gcc -g console.o sentence.o text.o stringswork.o menu.o cw.o -o cw

cw.o: cw.c console.h sentence.h text.h stringswork.h menu.h
	gcc -g -c cw.c

menu.o: menu.h menu.c
	gcc -g -c menu.c

stringswork.o: stringswork.h stringswork.c
	gcc -g -c stringswork.c

text.o: text.h text.c
	gcc -g -c text.c

console.o: console.h console.c
	gcc -g -c console.c

sentence.o: sentence.h sentence.c
	gcc -g -c sentence.c

clean:
	rm *.o