SOURCES=$(wildcard sources/*.c)
OBJECTS := $(patsubst sources/%.c,sources/%.o,$(SOURCES))
CFLAGS = -g

all: cw

cw: $(OBJECTS)
	gcc $(CFLAGS) -std=gnu99 $^ -o cw

sources/%.o : sources/%.c
	gcc $(CFLAGS) -std=gnu99 -c $< -o $@


clean_objects:
	rm -f $(OBJECTS)

clean:
	rm -rf sources/*.o cw
