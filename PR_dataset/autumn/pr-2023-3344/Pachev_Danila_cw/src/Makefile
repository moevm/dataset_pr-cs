all: main.o replace_digits.o read_text.o check_cyrillic.o print_words.o sort_sentence.o change_sentence_order.o begin.o replace_word.o
	gcc main.o replace_digits.o read_text.o check_cyrillic.o print_words.o sort_sentence.o change_sentence_order.o begin.o replace_word.o -o cw
main.o: main.c
	gcc -c main.c
replace_digits.o: replace_digits.c replace_digits.h
	gcc -c replace_digits.c
read_text.o: read_text.c read_text.h
	gcc -c read_text.c
check_cyrillic.o: check_cyrillic.c check_cyrillic.h
	gcc -c check_cyrillic.c
print_words.o: print_words.c print_words.h
	gcc -c print_words.c
sort_sentence.o: sort_sentence.c sort_sentence.h
	gcc -c sort_sentence.c
change_sentence_order.o: change_sentence_order.c change_sentence_order.h
	gcc -c change_sentence_order.c
begin.o: begin.c begin.h
	gcc -c begin.c
replace_word.o: replace_word.c replace_word.h
	gcc -c replace_word.c




