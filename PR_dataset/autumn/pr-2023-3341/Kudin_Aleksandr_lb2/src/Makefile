CC = gcc
CFLAGS = -Wall -std=c99
SRCS = menu.c index_first_negative.c index_last_negative.c multi_between_negative.c multi_before_and_after_negative.c
OBJS = $(SRCS:.c=.o)
TARGET = menu

all: $(TARGET)

$(TARGET): $(OBJS)
 $(CC) $(CFLAGS) -o $@ $^

%.o: %.c
 $(CC) $(CFLAGS) -c $<

clean:
 rm -f $(OBJS) $(TARGET)
