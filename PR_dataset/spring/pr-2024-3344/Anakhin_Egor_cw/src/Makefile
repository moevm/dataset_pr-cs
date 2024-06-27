CC = g++
CPPFLAGS = -std=c++11 -O3 -w
LDFLAGS = -lstdc++ -lm
MAKEFLAGS += -j8
SRCDIRS = . images_functions input_functions
SOURCES = $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.cpp))
OBJECTS = $(patsubst %.cpp, %.o, $(SOURCES))

%.o: %.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

cw: $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o cw

clean: 
	rm -f $(OBJECTS) cw