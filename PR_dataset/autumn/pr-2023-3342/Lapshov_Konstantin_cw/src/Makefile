CC=gcc
CFLAGS=-c -std=c99

all: main.o structures.o text_io.o get_unique_words.o change_digits.o sort_text.o change_cyrillic_sentence.o change_text.o
		$(CC) main.o structures.o text_io.o get_unique_words.o change_digits.o sort_text.o change_cyrillic_sentence.o change_text.o -o cw

main.o: main.c structures.h text_io.h get_unique_words.h change_digits.h sort_text.h change_cyrillic_sentence.h change_text.h
		$(CC) $(CFLAGS) main.c

structures.o: structures.c structures.h
		$(CC) $(CFLAGS) structures.c

text_io.o: text_io.c text_io.h structures.h
		$(CC) $(CFLAGS) text_io.c

get_unique_words.o: get_unique_words.c get_unique_words.h structures.h
		$(CC) $(CFLAGS) get_unique_words.c

change_digits.o: change_digits.c change_digits.h structures.h
		$(CC) $(CFLAGS) change_digits.c

sort_text.o: sort_text.c sort_text.h structures.h
		$(CC) $(CFLAGS) sort_text.c

change_cyrillic_sentence.o: change_cyrillic_sentence.c change_cyrillic_sentence.h structures.h
		$(CC) $(CFLAGS) change_cyrillic_sentence.c

change_text.o: change_text.c change_text.h structures.h
		$(CC) $(CFLAGS) change_text.c

clean:
		rm *.o