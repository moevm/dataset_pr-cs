CC = g++
CFLAGS = -std=c++14
OBJS = main.o rotate_func.o drawing_funcs.o additional_funcs.o
FILES = ./main.cpp sources/rotate_func.cpp sources/drawing_funcs.cpp sources/additional_funcs.cpp

fast: cw

cw: $(FILES)
	$(CC) $(CFLAGS) -o cw $(FILES)

clean:
	rm -rf *.o headers/*.hpp.gch cw