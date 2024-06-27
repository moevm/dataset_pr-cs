all : delete_sentences.o double_word.o dictionary.o distribute.o free_memory.o help.o input_text.o main.o output.o output_special_wchar.o process_text.o replace_numbers.o transliteration.o
	gcc delete_sentences.o double_word.o dictionary.o distribute.o free_memory.o help.o input_text.o main.o output.o output_special_wchar.o process_text.o replace_numbers.o transliteration.o -o cw
	rm *.o

delete_sentences.o: delete_sentences.c delete_sentences.h structures.h
	gcc -c delete_sentences.c

dictionary.o: dictionary.c dictionary.h
	gcc -c dictionary.c

distribute.o: distribute.c distribute.h structures.h output.h transliteration.h dictionary.h output_special_wchar.h replace_numbers.h delete_sentences.h help.h
	gcc -c distribute.c

free_memory.o: free_memory.c free_memory.h structures.h
	gcc -c free_memory.c

help.o: help.c help.h
	gcc -c help.c

input_text.o: input_text.c input_text.h structures.h
	gcc -c input_text.c

main.o: main.c structures.h input_text.h process_text.h distribute.h free_memory.h output.h transliteration.h dictionary.h output_special_wchar.h replace_numbers.h delete_sentences.h help.h
	gcc -c main.c

output.o: output.c output.h structures.h
	gcc -c output.c

output_special_wchar.o: output_special_wchar.c output_special_wchar.h structures.h
	gcc -c output_special_wchar.c

process_text.o: process_text.c process_text.h structures.h delete_sentences.h
	gcc -c process_text.c

replace_numbers.o: replace_numbers.c replace_numbers.h structures.h dictionary.h
	gcc -c replace_numbers.c

transliteration.o: transliteration.c transliteration.h structures.h dictionary.h
	gcc -c transliteration.c

double_word.o: double_word.c double_word.h structures.h
	gcc -c double_word.c
