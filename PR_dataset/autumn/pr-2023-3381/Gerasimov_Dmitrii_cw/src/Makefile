all: main.o dyn_array.o sentence_processing.o textio.o
	gcc main.o dyn_array.o sentence_processing.o textio.o -o cw

main.o: main.c
	gcc -c main.c

dyn_array.o: dyn_array.c
	gcc -c dyn_array.c

sentence_processing.o: sentence_processing.c
	gcc -c sentence_processing.c

textio.o: textio.c
	gcc -c textio.c