all: cw clean

cw: cw.o input_output.o image.o toolkit.o
	gcc -g cw.o image.o input_output.o toolkit.o -o cw -lm

cw.o: cw.c image.h input_output.h toolkit.h
	gcc -g -c cw.c

input_output.o: input_output.c input_output.h
	gcc -g -c input_output.c
	
image.o: image.c image.h 
	gcc -g -c image.c

toolkit.o: toolkit.c toolkit.h input_output.h
	gcc -g -c toolkit.c
	
clean:
	rm -rf *.o
