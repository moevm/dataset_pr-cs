all: main.o prepare.o delete_two_language_sentences.o leave.o palindromes.o sort_latin.o special_symbol.o start_and_choose_function.o big_word.o
	gcc main.o prepare.o delete_two_language_sentences.o leave.o palindromes.o sort_latin.o special_symbol.o start_and_choose_function.o big_word.o -o cw
main.o: main.c start_and_choose_function.h
	gcc -c main.c
prepare.o: prepare.c prepare.h structs.h leave.h
	gcc -c prepare.c
delete_two_language_sentences.o: delete_two_language_sentences.c delete_two_language_sentences.h structs.h leave.h
	gcc -c delete_two_language_sentences.c
leave.o: leave.c leave.h
	gcc -c leave.c
palindromes.o: palindromes.c palindromes.h structs.h leave.h
	gcc -c palindromes.c
sort_latin.o: sort_latin.c sort_latin.h structs.h
	gcc -c sort_latin.c
special_symbol.o: special_symbol.c special_symbol.h structs.h leave.h
	gcc -c special_symbol.c
start_and_choose_function.o: start_and_choose_function.c start_and_choose_function.h structs.h prepare.h palindromes.h sort_latin.h delete_two_language_sentences.h special_symbol.h leave.h big_word.h
	gcc -c start_and_choose_function.c 
big_word.o: big_word.h big_word.c structs.h leave.h
	gcc -c big_word.c
clean:
	rm -rf *o
