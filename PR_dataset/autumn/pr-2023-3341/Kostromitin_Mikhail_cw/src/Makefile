CC = gcc
CFLAGS = -Wall

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
TARGET = cw

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)