.PHONY: all clean

all: cw

cw: main.c
	gcc -o cw -I/usr/include/libpng16 main.c -lpng16 -lm

clean:
	rm -f cw
