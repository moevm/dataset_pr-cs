TARGET = cw
CC = gcc
CFLAGS = -g
SRC=$(wildcard $(SOURCE)*.cpp)
OBJ=$(patsubst $(SOURCE)%.cpp, $(BIN)%.o, $(SRC))

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $^ $(CFLAGS) -lpng -o $@

main.o: main.c
	$(CC) $^ $(CFLAGS) -c $< -lpng -o $@

image_proccessing.o: image_proccessing/image_proccessing.c image_proccessing/image_proccessing.h 
	$(CC) -c $< -lpng -o $@

file_manager.o: file_manager/file_manager.c file_manager/file_manager.h
	$(CC) -c $< -lpng -o $@

help.o: help/help.c help/help.h structs/struct.h
	$(CC) -c $< -lpng -o $@

clean:
	rm -rf *.o