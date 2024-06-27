CC=gcc
CFLAGS=-std=c99 -D_GNU_SOURCE

all: cw

cw: sentence.o text.o get_text.o print_number_of_occurences_of_all_words.o replace_non_alfa_chars.o sort_sentences_by_english_letter_count.o delete_sentences_that_have_special_chars_and_no_uppercase_letters.o replace_words.o cw.o
	${CC} $^ -o $@ ${CFLAGS}

sentence.o: sentence.c sentence.h
	${CC} -c $< ${CFLAGS}

text.o: text.c text.h sentence.h
	${CC} -c $< ${CFLAGS}

get_text.o: get_text.c get_text.h text.h sentence.h
	${CC} -c $< ${CFLAGS}

print_number_of_occurences_of_all_words.o: print_number_of_occurences_of_all_words.c print_number_of_occurences_of_all_words.h text.h sentence.h
	${CC} -c $< ${CFLAGS}

replace_non_alfa_chars.o: replace_non_alfa_chars.c replace_non_alfa_chars.h text.h sentence.h
	${CC} -c $< ${CFLAGS}

sort_sentences_by_english_letter_count.o: sort_sentences_by_english_letter_count.c sort_sentences_by_english_letter_count.h text.h sentence.h
	${CC} -c $< ${CFLAGS}

delete_sentences_that_have_special_chars_and_no_uppercase_letters.o: delete_sentences_that_have_special_chars_and_no_uppercase_letters.c delete_sentences_that_have_special_chars_and_no_uppercase_letters.h text.h sentence.h
	${CC} -c $< ${CFLAGS}

replace_words.o: replace_words.c replace_words.h text.h sentence.h
	${CC} -c $< ${CFLAGS}

cw.o: cw.c sentence.h text.h get_text.h print_number_of_occurences_of_all_words.h replace_non_alfa_chars.h sort_sentences_by_english_letter_count.h delete_sentences_that_have_special_chars_and_no_uppercase_letters.h replace_words.h
	${CC} -c $< ${CFLAGS}

clean:
	rm *.o cw
