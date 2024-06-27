
CC = g++

all: main.o pngdata.o image.o square.o inverse.o exchange.o freqcolor.o input_arguments.o
	$(CC) main.o pngdata.o image.o input_arguments.o square.o inverse.o exchange.o freqcolor.o -lz -o cw

main.o: main.cpp image.hpp
	$(CC) -c main.cpp

pngdata.o: pngdata.cpp pngdata.hpp
	$(CC) -c pngdata.cpp

image.o: image.cpp image.hpp
	$(CC) -c image.cpp

input_arguments.o: input_arguments.cpp input_arguments.hpp
	$(CC) -c input_arguments.cpp

square.o: square.cpp square.hpp
	$(CC) -c square.cpp

inverse.o: inverse.cpp inverse.hpp
	$(CC) -c inverse.cpp

exchange.o: exchange.cpp exchange.hpp
	$(CC) -c exchange.cpp

freqcolor.o: freqcolor.cpp freqcolor.hpp
	$(CC) -c freqcolor.cpp

clear:
	rm *.o
