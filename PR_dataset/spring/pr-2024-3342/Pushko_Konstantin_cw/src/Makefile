CXX = g++
CXXFLAGS = -std=c++11 -Wall -Werror
LDLIBS = -lpng

SRCS = main.cpp png_class.cpp file_interactions.cpp input_system.cpp
OBJS = $(SRCS:.cpp=.o)
HEADERS = png_class.h file_interactions.h input_system.h

all: $(OBJS)
	$(CXX) $(CXXFLAGS) -o cw $(OBJS) $(LDLIBS)

main.o: main.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

png_class.o: png_class.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c png_class.cpp -o png_class.o

file_interactions.o: file_interactions.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c file_interactions.cpp -o file_interactions.o

input_system.o: input_system.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c input_system.cpp -o input_system.o

clean:
	rm -f $(OBJS)
