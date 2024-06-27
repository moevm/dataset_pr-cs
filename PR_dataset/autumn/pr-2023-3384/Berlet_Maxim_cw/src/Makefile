all: main.o printN.o mfuncs.o mclean.o inputfuncs.o
	gcc main.o printN.o mfuncs.o mclean.o inputfuncs.o -o cw
main.o: main.c
	gcc -c main.c
printN.o: printN.c printN.h
	gcc -c printN.c
mfuncs.o: mfuncs.c mfuncs.h
	gcc -c mfuncs.c
mclean.o: mclean.c mclean.h
	gcc -c mclean.c
inputfuncs.o: inputfuncs.c inputfuncs.h
	gcc -c inputfuncs.c


clean_all:
	rm *.o
	rm cw
