all: main.o Circle.o ImageRedactor.o Line.o PngReader.o Rectangle.o
	g++ main.o Circle.o ImageRedactor.o Line.o PngReader.o Rectangle.o -o ./cw -std=c++17 -lpng

main.o: main.cpp
	g++ -c -std=c++17 main.cpp

Circle.o: ./lib/Circle.cpp
	g++ -c -std=c++17 ./lib/Circle.cpp

ImageRedactor.o: ./lib/ImageRedactor.cpp
	g++ -c -std=c++17 ./lib/ImageRedactor.cpp

Line.o: ./lib/Line.cpp
	g++ -c -std=c++17 ./lib/Line.cpp

PngReader.o: ./lib/PngReader.cpp
	g++ -c -std=c++17 -lpng ./lib/PngReader.cpp

Rectangle.o: ./lib/Rectangle.cpp
	g++ -c -std=c++17 ./lib/Rectangle.cpp