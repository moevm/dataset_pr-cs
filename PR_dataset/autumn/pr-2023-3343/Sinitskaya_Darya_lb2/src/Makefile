CC = gcc
CFLAGS = -Wall

SOURCES = menu.c index_first_negative.c index_last_negative.c multi_between_negative.c multi_before_and_after_negative.c
HEADERS = index_first_negative.h index_last_negative.h multi_between_negative.h multi_before_and_after_negative.h

all: menu

menu: $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o menu $(SOURCES)

clean:
	rm -f menu
