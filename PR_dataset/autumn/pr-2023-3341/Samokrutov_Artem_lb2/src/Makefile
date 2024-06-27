TARGET = menu
CC = gcc
CFLAGS = -Wall -std=c99

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))

all : $(TARGET)

$(TARGET) : $(OBJ)
	$(CC)  $^ -o $@

%.o : %.c
	$(CC) -c $< -o $@

clean :
	rm -f $(TARGET) *.o
