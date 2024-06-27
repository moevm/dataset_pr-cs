all: cw

cw: menu.o getcommand.o readtext.o preprocessing.o printtext.o freetext.o bananapplesearch.o convertnumsandalpha.o siftedoutput.o sorttextnums.o printduplicates.o
	gcc -std=gnu99 menu.o getcommand.o readtext.o preprocessing.o printtext.o freetext.o bananapplesearch.o convertnumsandalpha.o siftedoutput.o sorttextnums.o printduplicates.o -o cw

menu.o: menu.c
	gcc -std=gnu99 -c menu.c

getcommand.o: getcommand.c getcommand.h
	gcc -std=gnu99 -c getcommand.c

readtext.o: readtext.c readtext.h
	gcc -std=gnu99 -c readtext.c

preprocessing.o: preprocessing.c preprocessing.h
	gcc -std=gnu99 -c preprocessing.c

printtext.o: printtext.c printtext.h
	gcc -std=gnu99 -c printtext.c

freetext.o: freetext.c freetext.h
	gcc -std=gnu99 -c freetext.c

bananapplesearch.o: bananapplesearch.c bananapplesearch.h
	gcc -std=gnu99 -c bananapplesearch.c

convertnumsandalpha.o: convertnumsandalpha.c convertnumsandalpha.h
	gcc -std=gnu99 -c convertnumsandalpha.c

siftedoutput.o: siftedoutput.c siftedoutput.h
	gcc -std=gnu99 -c siftedoutput.c

sorttextnums.o: sorttextnums.c sorttextnums.h
	gcc -std=gnu99 -c sorttextnums.c

printduplicates.o: printduplicates.c printduplicates.h
	gcc -std=gnu99 -c printduplicates.c

clear:
	rm *.o
