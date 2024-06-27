all: cw

cw: main.o utils.o draw.o headers/defines.h
	gcc main.o utils.o draw.o -lm -o cw

draw.o: core/draw.c headers/draw.h
	gcc -c ./core/draw.c

utils.o: core/utils.c headers/utils.h
	gcc -c ./core/utils.c

main.o: core/main.c headers/main.h
	gcc -c ./core/main.c

clean:
	rm -rf *.o cw *.bmp
