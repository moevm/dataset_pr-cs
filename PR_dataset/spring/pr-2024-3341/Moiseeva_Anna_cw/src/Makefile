all: cw clean

cw: cw.o cli.o file_handling.o image_processing.o
	gcc -g cw.o cli.o file_handling.o image_processing.o -o cw

cw.o: cw.c cli/cli.h file_handling/file_handling.h image_processing/image_processing.h
	gcc -c cw.c

cli.o: cli/cli.c cli/cli.h file_handling/file_handling.h image_processing/image_processing.h
	gcc -c cli/cli.c 

file_handling.o: file_handling/file_handling.c file_handling/file_handling.h 
	gcc -c file_handling/file_handling.c

image_processing.o: image_processing/image_processing.c image_processing/image_processing.h
	gcc -c image_processing/image_processing.c

clean:
	rm -rf *.o

