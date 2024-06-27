CC = gcc
CFLAGS = -lpng -lm
SOURCE = $(wildcard source/*.c)
OBJECTS = $(patsubst source/%.c,source/%.o,$(SOURCE))

all: cw

source/%.o : source/%.c
	$(CC) -c $< -o $@

cw: $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) -o cw

clean:
	rm -rf source/*.o cw