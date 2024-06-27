
all: cw

cw: checkers.o bmpfunc.o functions.o cli.o secondary_func.o
	gcc -o cw $^ -lm

checkers.o: checkers.c structurs.h checkers.h
	gcc -c $<

bmpfunc.o: bmpfunc.c structurs.h bmpfunc.h secondary_func.h
	gcc -c $<

secondary_func.o: secondary_func.c structurs.h secondary_func.h
	gcc -c $<

functions.o: functions.c structurs.h functions.h secondary_func.h
	gcc -c $<

cli.o: cli.c structurs.h checkers.h bmpfunc.h checkers.h
	gcc -c $<

clean:
	rm -f *.o cw
