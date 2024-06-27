all: cw 
cw: del.o free.o func1.o func2.o func3.o func4.o func9.o main.o sio.o 
	gcc del.o free.o func1.o func2.o func3.o func4.o func9.o main.o sio.o  -o cw
main.o: main.c del.h free.h func1.h func2.h func3.h func4.h sio.h struct.h
	gcc -c main.c
del.o: del.c del.h struct.h
	gcc -c del.c
free.o: free.c free.h struct.h
	gcc -c free.c
func1.o: func1.c func1.h struct.h sio.h
	gcc -c func1.c
func2.o: func2.c func2.h struct.h sio.h
	gcc -c func2.c
func3.o: func3.c func3.h struct.h sio.h
	gcc -c func3.c
func4.o: func4.c func4.h struct.h sio.h
	gcc -c func4.c
func9.o: func9.c func9.h struct.h 
	gcc -c func9.c	
sio.o: sio.c sio.h struct.h
	gcc -c sio.c
clean:
	rm -rf *.o cw

