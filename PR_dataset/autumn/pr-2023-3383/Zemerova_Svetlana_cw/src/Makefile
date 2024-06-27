all: cw

cw: main.o input_output.o functions.o dopfunctions.o freememory.o
	gcc main.o input_output.o functions.o dopfunctions.o freememory.o -o cw

main.o: main.c struct.h input_output.h freememory.h functions.h 
	gcc -c main.c
	
input_output.o: input_output.c input_output.h functions.h struct.h
	gcc -c input_output.c
	
functions.o: functions.c functions.h struct.h
	gcc -c functions.c
	
dopfunctions.o: dopfunctions.c functions.h struct.h
	gcc -c dopfunctions.c
	
freememory.o: freememory.c freememory.h struct.h
	gcc -c freememory.c 
	
clean:
	rm *.o cw
