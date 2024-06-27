all: cw clean

cw: main.o bmp_functions.o flags_processing.o info_functions.o
	gcc main.o bmp_functions.o flags_processing.o info_functions.o -o cw

main.o: main.c structures.h info_functions.h flags_processing.h bmp_functions.h
	gcc -c main.c

bmp_functions.o: bmp_functions.c bmp_functions.h
	gcc -c bmp_functions.c

info_functions.o: info_functions.c info_functions.h
	gcc -c info_functions.c

flags_processing.o: flags_processing.c flags_processing.h info_functions.h
	gcc -c flags_processing.c
clean:
	rm -rf *.o
