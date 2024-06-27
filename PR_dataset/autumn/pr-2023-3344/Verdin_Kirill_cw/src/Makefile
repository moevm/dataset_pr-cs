CC=gcc
CFLAGS=-std=c99 -D_GNU_SOURCE

all: cw

cw: cw.o word.o sentence.o text.o input_text.o replace_digit.o print_if_last_word_of_previous_sentence_is_in_current_sentence.o sort_sentences.o delete_sentence_if_len_is_less_than_2.o function9.o
	${CC} $^ -o $@ ${CFLAGS}

word.o: word.c word.h
	${CC} -c $< ${CFLAGS}

sentence.o: sentence.c word.h sentence.h
	${CC} -c $< ${CFLAGS}

text.o:text.c word.h sentence.h text.h
	${CC} -c $< ${CFLAGS}
	
input_text.o: input_text.c word.h sentence.h text.h input_text.h
	${CC} -c $< ${CFLAGS}

replace_digit.o:replace_digit.c word.h sentence.h text.h replace_digit.h
	${CC} -c $< ${CFLAGS}

print_if_last_word_of_previous_sentence_is_in_current_sentence.o: print_if_last_word_of_previous_sentence_is_in_current_sentence.c word.h sentence.h text.h print_if_last_word_of_previous_sentence_is_in_current_sentence.h
	${CC} -c $< ${CFLAGS}

sort_sentences.o: sort_sentences.c word.h sentence.h text.h sort_sentences.h
	${CC} -c $< ${CFLAGS}

delete_sentence_if_len_is_less_than_2.o: delete_sentence_if_len_is_less_than_2.c word.h sentence.h text.h delete_sentence_if_len_is_less_than_2.h
	${CC} -c $< ${CFLAGS}

function9.o: function9.c function9.h word.h sentence.h text.h
	${CC} -c $< ${CFLAGS}

cw.o : cw.c word.h sentence.h text.h input_text.h replace_digit.h print_if_last_word_of_previous_sentence_is_in_current_sentence.h sort_sentences.h delete_sentence_if_len_is_less_than_2.h function9.h
	${CC} -c $< ${CFLAGS}

clean:
	rm *.o cw
