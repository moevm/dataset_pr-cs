CC = gcc
CFLAGS = -Wall -Wextra

TARGET = cw
SRCS = main.c bmp_reader.c print_func.c bmp_draw.c change_bmp.c processing_data.c
OBJS = $(SRCS:.c=.o)
HDRS = bmp_reader.h print_func.h processing_bmp.h processing_data.h

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) -lm

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(TARGET) $(OBJS)

