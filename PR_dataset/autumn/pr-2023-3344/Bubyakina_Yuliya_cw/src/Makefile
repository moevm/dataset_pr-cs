CC=gcc
CFLAGS=-std=c99 -D_GNU_SOURCE

cw: sentence.o text.o input.o transliterate.o print_special_symbols.o replace_nums.o delete_sentences_with_odd_numbers.o cw.o repeat_sentences.o
	${CC} $^ -o $@ ${CFLAGS}

sentence.o: sentence.c sentence.h
	${CC} -c $< ${CFLAGS}

text.o: text.c text.h sentence.h
	${CC} -c $< ${CFLAGS}

input.o: input.c input.h text.h sentence.h
	${CC} -c $< ${CFLAGS}

repeat_sentences.o: repeat_sentences.c repeat_sentences.h text.h sentence.h
	${CC} -c $< ${CFLAGS}

transliterate.o: transliterate.c transliterate.h text.h sentence.h
	${CC} -c $< ${CFLAGS}

print_special_symbols.o: print_special_symbols.c print_special_symbols.h text.h sentence.h
	${CC} -c $< ${CFLAGS}

replace_nums.o: replace_nums.c replace_nums.h text.h sentence.h
	${CC} -c $< ${CFLAGS}

delete_sentences_with_odd_numbers.o: delete_sentences_with_odd_numbers.c delete_sentences_with_odd_numbers.h text.h sentence.h
	${CC} -c $< ${CFLAGS}

cw.o: cw.c sentence.h text.h input.h transliterate.h print_special_symbols.h replace_nums.h delete_sentences_with_odd_numbers.h repeat_sentences.h
	${CC} -c $< ${CFLAGS}

clean:
	rm *.o cw
