TARGET = cw
CC = gcc
LIBS = ./bmp ./drawing ./help ./option ./structs
CFLAGS = $(foreach lib, $(LIBS), -I$(lib))
SRC = $(wildcard *.c) $(wildcard **/*.c)
OBJ = $(patsubst */%.c, $(PREF_BIN)%.o, $(SRC))

all : $(TARGET)

$(TARGET) : $(OBJ)
	$(CC) $(CFLAGS) $^ -lm -o $@

clean :
	rm $(TARGET) *.o