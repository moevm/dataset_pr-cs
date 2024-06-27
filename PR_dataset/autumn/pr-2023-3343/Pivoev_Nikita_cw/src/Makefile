SOURCES = $(wildcard sources/*.c)
OBJECTS = $(patsubst sources/%.c,sources/%.o,$(SOURCES))
CC = gcc
CFLAGS = -g

all: cw

cw: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o cw

sources/%.o : sources/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf sources/*.o cw
