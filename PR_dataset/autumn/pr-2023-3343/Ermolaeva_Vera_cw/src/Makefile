SOURCES = $(wildcard sources/*.c)
HEADERS = $(wildcard include/*.h)

FILES = $(patsubst sources/%.c, sources/%.o, $(SOURCES))
FLAGS = -c

all: $(FILES)
	gcc $(FILES) -o cw

main.o: main.c $(HEADERS)
	gcc $(FLAGS) main.c

count_minutes.o: count_minutes.c struct.h
	gcc $(FLAGS) count_minutes.c

remove_sentences.o: remove_sentences.c struct.h
	gcc $(FLAGS) remove_sentences.c

replace_symbols.o: replace_symbols.c struct.h
	gcc $(FLAGS) replace_symbols.c

sort_sentences.o: sort_sentences.c struct.h
	gcc $(FLAGS) sort_sentences.c

struct.o: struct.c
	gcc $(FLAGS) struct.c

text_processing.o: text_processing.c struct.h
	gcc $(FLAGS) text_processing.c

clean:
	rm -rf sources/*.o
	rm cw