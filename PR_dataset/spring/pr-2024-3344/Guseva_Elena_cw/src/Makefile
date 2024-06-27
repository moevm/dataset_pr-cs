FLAGS = -std=c99

all: cw

cw: main.o functions.o work_with_bmp.o checkers.o 
	gcc -o cw $^ -lm

main.o: main.c structs.h functions.h work_with_bmp.h checkers.h 
	gcc -c $<

functions.o: functions.c structs.h functions.h
	gcc -c $<

work_with_bmp.o: work_with_bmp.c structs.h work_with_bmp.h
	gcc -c $<

checkers.o: checkers.c structs.h checkers.h
	gcc -c $<

clean:
	rm -f *.o cw