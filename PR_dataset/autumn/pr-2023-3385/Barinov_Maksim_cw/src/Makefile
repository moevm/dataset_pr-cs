all: cw
cw: main.o func.o InputOutput.o
	gcc main.o func.o  InputOutput.o -o cw
main.o: main.c func.h Struct.h
	gcc -c main.c
func.o: func.c func.h Struct.h
	gcc -c func.c
InputOutput.o: InputOutput.c InputOutput.h Struct.h
	gcc -c InputOutput.c
clean:
	rm -rf *.o

