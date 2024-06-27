MAKEFLAGS += --silent
СС = gcc
FLAGS = -std=gnu99
CLEAN = rm -f *.o cw

all: cw

cw: main.o code_runner.o delete_capital.o input_func.o print_func.o shift_words.o unique_symbols.o words_len.o replace_big_words.o
	$(CC) $(FLAGS) -o cw main.o code_runner.o delete_capital.o input_func.o print_func.o shift_words.o unique_symbols.o words_len.o replace_big_words.o || $(CLEAN)

main.o: main.c structures.h
	$(CC) $(FLAGS) -c main.c || $(CLEAN)

code_runner.o: code_runner.c code_runner.h
	$(CC) $(FLAGS) -c code_runner.c || $(CLEAN)

delete_capital.o: delete_capital.c delete_capital.h
	$(CC) $(FLAGS) -c delete_capital.c || $(CLEAN)

input_func.o: input_func.c input_func.h
	$(CC) $(FLAGS) -c input_func.c || $(CLEAN)

print_func.o: print_func.c print_func.h
	$(CC) $(FLAGS) -c print_func.c || $(CLEAN)

shift_words.o: shift_words.c shift_words.h
	$(CC) $(FLAGS) -c shift_words.c || $(CLEAN)

unique_symbols.o: unique_symbols.c unique_symbols.h
	$(CC) $(FLAGS) -c unique_symbols.c || $(CLEAN)

words_len.o: words_len.c words_len.h
	$(CC) $(FLAGS) -c words_len.c || $(CLEAN)

replace_big_words.o: replace_big_words.c replace_big_words.h
	$(CC) $(FLAGS) -c replace_big_words.c || $(CLEAN)

clean:
	$(CLEAN)