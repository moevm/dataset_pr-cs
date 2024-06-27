CC = gcc

all: cw

cw: main.o read_text.o is_single_sentence.o memory_error.o compare_multiply.o check_digits_and_symbs.o find_single_words.o is_word_in_array.o find_dates.o is_date_correct.o
	$(CC) -o cw main.o read_text.o is_single_sentence.o memory_error.o compare_multiply.o check_digits_and_symbs.o find_single_words.o is_word_in_array.o find_dates.o is_date_correct.o

main.o: main.c structs.h
	$(CC) -c main.c

read_text.o: read_text.c structs.h
	$(CC) -c read_text.c

is_single_sentence.o: is_single_sentence.c structs.h
	$(CC) -c is_single_sentence.c

memory_error.o: memory_error.c
	$(CC) -c memory_error.c

compare_multiply.o: compare_multiply.c structs.h
	$(CC) -c compare_multiply.c

check_digits_and_symbs.o: check_digits_and_symbs.c structs.h
	$(CC) -c check_digits_and_symbs.c

find_single_words.o: find_single_words.c structs.h
	$(CC) -c find_single_words.c

is_word_in_array.o: is_word_in_array.c
	$(CC) -c is_word_in_array.c

find_dates.o: find_dates.c structs.h
	$(CC) -c find_dates.c

is_date_correct.o: is_date_correct.c
	$(CC) -c is_date_correct.c

clean:
	rm -f *.o cw