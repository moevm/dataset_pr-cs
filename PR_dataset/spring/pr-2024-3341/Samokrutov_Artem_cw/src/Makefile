TARGET = cw
CC = gcc

LIBS = ./bmp ./drawing ./error ./options ./structures

CFLAGS = -Wall -std=gnu99 $(foreach lib, $(LIBS), -I$(lib))

CORE = $(wildcard *.c) $(wildcard **/*.c)
OBJ = $(patsubst */%.c, $(PREF_BIN)%.o, $(CORE))

all : $(TARGET)

$(TARGET) : $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

clean :
	rm -rf $(TARGET)
