SOURCES = $(wildcard sources/*.c)
OBJECTS = $(patsubst sources/%.c,sources/%.o,$(SOURCES))
CC = gcc
CFLAGS = -lpng -lm

all: cw

cw: $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) -o cw

sources/%.o : sources/%.c
	$(CC) -c $< -o $@

clean:
	rm -rf sources/*.o cw