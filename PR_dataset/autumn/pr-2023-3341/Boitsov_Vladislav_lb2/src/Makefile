CC = gcc
CFLAGS = -Wall -std=gnu99
EXECUTABLE=menu
SOURCES = menu.c index_first_zero.c index_last_zero.c sum_between.c sum_before_and_after.c
OBJECTS = $(SOURCES:.c=.o)

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) -c $<
	
clean:
	rm $(EXECUTABLE) *.o