CC=gcc

TARGET=cw

OBJECTS=cw.o get-option.o give-initial-information.o process-command.o give-info-about-functions.o check-command-character.o read-text.o return-reworked-text.o output-struct-of-text.o print-uniqual-words.o split-sentences-on-words.o sort-by-length.o delete-special-sentences.o replace-date.o free-text.o nine-func.o

all: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

%.o: functions/%.c
	$(CC) -c $(CFLAGS) $<
	
clear:
	rm *.o