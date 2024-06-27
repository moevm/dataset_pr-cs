
CC=gcc
headers=menu.h text_base_funct.h input_output_text.h anagram_funct.h wchar_checks.h replace_vowels.h breaks_in_sentence.h replace_words.h


all: main.o menu.o text_base_funct.o input_output_text.o breaks_in_sentence.o anagram_funct.o wchar_checks.o replace_vowels.o replace_words.o
	$(CC) main.o input_output_text.o text_base_funct.o anagram_funct.o wchar_checks.o replace_vowels.o breaks_in_sentence.o replace_words.o menu.o -o cw

main.o: main.c $(headers)
	$(CC) -c main.c

text_base_funct.o: text_base_funct.c $(headers)
	$(CC) -c text_base_funct.c

input_output_text.o: input_output_text.c $(headers)
	$(CC) -c input_output_text.c

anagram_funct.o: anagram_funct.c $(headers)
	$(CC) -c anagram_funct.c

wchar_checks.o: wchar_checks.c $(headers)
	$(CC) -c wchar_checks.c

replace_vowels.o: replace_vowels.c $(headers)
	$(CC) -c replace_vowels.c

breaks_in_sentence.o: breaks_in_sentence.c $(headers)
	$(CC) -c breaks_in_sentence.c

replace_words.o: replace_words.c $(headers)
	$(CC) -c replace_words.c

menu.o: menu.c $(headers)
	$(CC) -c menu.c

clear:
	rm -f *.o
	rm -f cw
