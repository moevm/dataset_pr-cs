CXX = g++
CXXFLAGS = -std=c++11

all: main

main: image_io.o image_processing.o input.o main.o
	$(CXX) $(CXXFLAGS) -o cw $^

image_io.o: image_io.cpp structs.h image_bmp.h
	$(CXX) $(CXXFLAGS) -c $<

image_processing.o: image_processing.cpp structs.h image_bmp.h
	$(CXX) $(CXXFLAGS) -c $<

input.o: input.cpp input.h structs.h
	$(CXX) $(CXXFLAGS) -c $<

main.o: main.cpp structs.h image_bmp.h input.h
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o main
