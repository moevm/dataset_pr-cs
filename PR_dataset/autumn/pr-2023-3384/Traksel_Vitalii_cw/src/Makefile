all: cw clean

cw: cw.o func.o getprint.o
	gcc cw.o func.o getprint.o -o cw
cw.o: cw.c func.h getprint.h
	gcc -c cw.c
func.o: func.c func.h getprint.h
	gcc -c func.c
getprint.o: getprint.c func.h getprint.h
	gcc -c getprint.c
clean:
	rm *.o
