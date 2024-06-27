# cw  - command line version
# gcw - gui version

CC     := g++
CFLAGS := $(shell pkg-config --cflags libpng) -g
LIBS   := $(shell pkg-config --libs libpng) -lm

OBJ    := obj

SRCS   := $(patsubst ./%, %, $(shell find -name '*.cpp')) 
INCS   := $(shell find -name '*.hpp')
DEPS   := $(patsubst %.cpp, $(OBJ)/%.d, $(SRCS))
OBJS   := $(patsubst %.cpp, $(OBJ)/%.o, $(SRCS))

.PHONY: all clean compile_commands

all: cw

$(OBJ)/%.o: %.cpp
	@mkdir -p $(shell dirname $@) 
	$(CC) -c -MMD -o $@ $< $(CFLAGS)

cw: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
clean:
	rm -rf obj cw
	rm -f compile_commands.json

compile_commands: clean
	bear -- make

-include $(DEPS)