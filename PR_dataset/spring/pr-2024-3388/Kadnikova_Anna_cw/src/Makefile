all: cw clean

cw: cw.o image.o io.o parser.o str.o
	gcc -g cw.o image.o io.o parser.o str.o -lpng -lm -o cw

cw.o: cw.c image.h io.h parser.h str.h
	gcc -g -c cw.c image.h io.h parser.h str.h

io.o: io.c io.h const.h image.h parser.h 
	gcc -g -c io.c io.h const.h image.h parser.h 

parser.o: parser.c parser.h str.h const.h
	gcc -g -c parser.c parser.h str.h const.h

image.o: image.c image.h const.h
	gcc -g -c image.c image.h const.h

str.o: str.c str.h const.h
	gcc -g -c str.c str.h const.h

clean:
	rm -rf *.o *.gch
