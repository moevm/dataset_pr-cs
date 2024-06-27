CC =g++
CFLAGS =-std=c++11

all: cw

cw: main.o bmp.o input.o
	${CC} $^ -o $@ ${CFLAGS}

bmp.o: bmp/bmp.cpp bmp/bmp.h
	${CC} -c $< ${CFLAGS}

input.o: input/input.cpp input/input.h bmp/bmp.h
	${CC} -c $< ${CFLAGS}

main.o: main.cpp input/input.h bmp/bmp.h 
	${CC} -c $< ${CFLAGS}

clean:
	rm *.o cw