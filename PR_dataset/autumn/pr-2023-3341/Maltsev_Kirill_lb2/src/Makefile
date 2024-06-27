TARGET = menu
CC = gcc
CFLAGS = -Wall -std=gnu99

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))

all : $(TARGET)

$(TARGET) : $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm $(TARGET) *.o
