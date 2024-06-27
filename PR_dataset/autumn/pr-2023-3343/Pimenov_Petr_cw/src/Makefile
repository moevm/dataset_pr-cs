CFLAGS = -std=gnu99

all: io.o main.o text_processing.o memory.o util.o
	mkdir -p build
	gcc $(CFLAGS) ./build/io.o ./build/main.o ./build/text_processing.o ./build/memory.o ./build/util.o -o cw
	cp cw ./build/cw

io.o: ./src/io.c ./src/data.h ./src/config.h ./src/io.h ./src/memory.h
	mkdir -p build
	gcc $(CFLAGS) -c ./src/io.c
	mv io.o ./build/io.o

main.o: ./src/main.c ./src/io.h ./src/text_processing.h ./src/data.h ./src/memory.h ./src/config.h
	mkdir -p build
	gcc $(CFLAGS) -c ./src/main.c
	mv main.o ./build/main.o

text_processing.o: ./src/text_processing.c ./src/data.h ./src/text_processing.h ./src/config.h ./src/util.h ./src/memory.h
	mkdir -p build
	gcc $(CFLAGS) -c ./src/text_processing.c
	mv text_processing.o ./build/text_processing.o

memory.o: ./src/memory.c ./src/memory.h ./src/data.h
	mkdir -p build
	gcc $(CFLAGS) -c ./src/memory.c
	mv memory.o ./build/memory.o

util.o: ./src/util.c ./src/util.h ./src/config.h ./src/data.h
	mkdir -p build
	gcc $(CFLAGS) -c ./src/util.c
	mv util.o ./build/util.o

.PHONY: clean
clean:
	rm -rf ./build cw