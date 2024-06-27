CC = gcc 
CFLAGS = -Wall -std=gnu99
TARGET = menu
SOURCES = menu.c index_first_negative.c index_last_negative.c sum_between_negative.c sum_before_and_after_negative.c choice.c input_data.c input_command.c
HEADERS = index_first_negative.h index_last_negative.h sum_between_negative.h sum_before_and_after_negative.h choice.h input_data.h input_command.h

all: $(TARGET)
$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clear: 
	rm -f $(TARGET)
