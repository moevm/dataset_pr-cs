CC=gcc
EXECUTABLENAME=cw
CFLAGS = -lpng -lm

SOURCES = $(wildcard source/*.c)
OBJECTS = $(patsubst source/%.c,source/%.o,$(SOURCES))

all: $(EXECUTABLENAME)

$(EXECUTABLENAME): $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) -o $(EXECUTABLENAME)

source/%.o: source/%.c
	$(CC) -I include -c $< -o $@

clean:
	rm -rf source/*.o $(EXECUTABLENAME)
