CC = gcc
CPPFLAGS = -lstdc++ -lm -O3
MAKEFLAGS += -j4
SRCDIRS = . input image_methods other
SOURCES = $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.cpp))
OBJECTS = $(patsubst %.cpp, %.o, $(SOURCES))

%.o: %.cpp
	$(CC) -c $< -o $@

cw: $(OBJECTS)
	$(CC) $(OBJECTS) $(CPPFLAGS) -o cw

clean: 
	rm -f $(OBJECTS) cw
