CC=gcc

CFLAGS=-g

TARGET=cw

OBJECTS=main.o colorizeText.o deleteNumbers.o findUpperCaseWords.o sortSentences.o textHandle.o textInputOutput.o

all: $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) -std=gnu99 -o $(TARGET)

%.o: %.c
	$(CC) -c $(CFLAGS) $<


debug: all
	valgrind --show-reachable=yes --leak-check=full --track-origins=yes ./$(TARGET)

clear:
	rm *.o