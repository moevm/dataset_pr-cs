all: main.o image.o draw.o tools.o
	gcc main.o image.o draw.o tools.o -o cw -lpng -lm

main.o: main.c image.h
	gcc -c main.c -o main.o

image.o: image.c image.h
	gcc -c image.c -o image.o

draw.o: draw.c draw.h image.h
	gcc -c draw.c -o draw.o

tools.o: tools.c tools.h draw.h image.h
	gcc -c tools.c -o tools.o

clear:
	rm -f main *.o