TARGET = cw
CC = gcc

LIBS = ./structs ./png_io ./args_parsing ./image_processing

CFLAGS = -Wall -std=gnu99 $(foreach lib, $(LIBS), -I$(lib))

CORE = $(wildcard *.c) $(wildcard **/*.c)
OBJ = $(patsubst */%.c, %.o, $(CORE))

all : $(TARGET)

$(TARGET) : $(OBJ)
	$(CC) $(CFLAGS) $^ -lm -lpng -o $@

clean :
	rm -rf $(TARGET)