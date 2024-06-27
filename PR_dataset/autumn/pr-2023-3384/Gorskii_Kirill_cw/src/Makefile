CC=gcc
CFLAGS=-Wall

.PHONY: all clean

all: cw

cw: obj/string.o obj/text.o obj/main.o obj/fatal_error.o
	$(CC) $(CFLAGS) obj/string.o obj/text.o obj/main.o obj/fatal_error.o -o cw

obj/string.o: string.h string.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -c -o obj/string.o string.c

obj/text.o: text.c text.h string.h
	@mkdir -p obj
	$(CC) $(CFLAGS) -c -o obj/text.o text.c

obj/main.o: main.c text.h fatal_error.h
	@mkdir -p obj
	$(CC) $(CFLAGS) -c -o obj/main.o main.c

obj/fatal_error.o: fatal_error.c fatal_error.h
	@mkdir -p obj
	$(CC) $(CFLAGS) -c -o obj/fatal_error.o fatal_error.c

clean:
	rm -rf obj
	rm cw
