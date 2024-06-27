cw: fotm.o main.o structures.o square.o filter.o rotate.o circle.o smalcheck.o check.o romb.o
	gcc fotm.o main.o structures.o square.o filter.o rotate.o circle.o smalcheck.o check.o romb.o -o cw
fotm.o: fotm.c fotm.h structures.o square.o filter.o
	gcc -c fotm.c
structures.o: structures.c structures.h
	gcc -c structures.c
square.o: square.c square.h structures.h
	gcc -c square.c
filter.o: filter.c filter.h
	gcc -c filter.c
rotate.o: rotate.c rotate.h
	gcc -c rotate.c
circle.o: circle.c circle.h
	gcc -c circle.c
check.o: check.c check.h
	gcc -c check.c
smalcheck.o: smalcheck.c smalcheck.h
	gcc -c smalcheck.c
romb.o: romb.c romb.h structures.o
	gcc -c romb.c
main.o: main.c
	gcc -c main.c
clean:
	rm -rf *.o main
