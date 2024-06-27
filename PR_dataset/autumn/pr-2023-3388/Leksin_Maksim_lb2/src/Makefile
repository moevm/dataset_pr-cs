CC = gcc
CFLAGS = -Wall -std=gnu99
TARGET = menu
SOURCES = menu.c abs_max.c abs_min.c diff.c sum.c answer.c array.c input_operation.c
HEADERS = abs_max.h abs_min.h diff.h sum.h answer.h array.h input_operation.h menu.h

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)
