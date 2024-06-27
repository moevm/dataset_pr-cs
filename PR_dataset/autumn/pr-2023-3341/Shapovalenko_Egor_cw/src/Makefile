all: main.o input.o processing.o text_processing.o output.o
	gcc main.o input.o processing.o text_processing.o output.o -o cw
main.o: main.c processing.h input.h output.h structures.h text_processing.h
	gcc -c main.c
input.o: input.c input.h
	gcc -c input.c
processing.o: processing.c processing.h input.h output.h structures.h text_processing.h
	gcc -c processing.c
text_processing.o: text_processing.c text_processing.h structures.h
	gcc -c text_processing.c
output.o: output.c output.h structures.h
	gcc -c output.c
clear:
	rm -r *.o cw