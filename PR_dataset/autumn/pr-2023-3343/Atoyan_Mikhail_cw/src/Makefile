SOURCES=$(wildcard sources/*.c)
OBJECTS := $(patsubst sources/%.c,sources/%.o,$(SOURCES))
FLAGS = -g

all: cw

cw: $(OBJECTS)
	gcc $(FLAGS) -std=gnu99 $^ -o cw

sources/%.o : sources/%.c
	gcc $(FLAGS) -std=gnu99 -c $< -o $@

clean_objects:
	rm -f $(OBJECTS)

clean:
	rm -rf sources/*.o cw

debug: cw
	gdb cw