TARGET = cw
CC = gcc

$(TARGET) : cw.o read_text.o basic_processing.o check_palindromes.o general_information.o remove_duplicate_sentences.o remove_mixed_alphabet_sentences.o replace_special_symbols.o sort_by_latin_letters.o 
	$(CC) cw.o read_text.o basic_processing.o check_palindromes.o general_information.o remove_duplicate_sentences.o remove_mixed_alphabet_sentences.o replace_special_symbols.o sort_by_latin_letters.o -o $(TARGET)

cw.o : cw.c read_text.h remove_duplicate_sentences.h general_information.h basic_processing.h check_palindromes.h replace_special_symbols.h sort_by_latin_letters.h remove_mixed_alphabet_sentences.h
	$(CC) -c cw.c -o cw.o 

read_text.o : read_text.c read_text.h
	$(CC) -c read_text.c -o read_text.o

basic_processing.o : basic_processing.c basic_processing.h read_text.h
	$(CC) -c basic_processing.c -o basic_processing.o

check_palindromes.o : check_palindromes.c check_palindromes.h read_text.h
	$(CC) -c check_palindromes.c -o check_palindromes.o

general_information.o : general_information.c general_information.h
	$(CC) -c general_information.c -o general_information.o

remove_duplicate_sentences.o : remove_duplicate_sentences.c remove_duplicate_sentences.h read_text.h
	$(CC) -c remove_duplicate_sentences.c -o remove_duplicate_sentences.o

remove_mixed_alphabet_sentences.o : remove_mixed_alphabet_sentences.c remove_mixed_alphabet_sentences.h read_text.h
	$(CC) -c remove_mixed_alphabet_sentences.c -o remove_mixed_alphabet_sentences.o

replace_special_symbols.o : replace_special_symbols.c replace_special_symbols.h read_text.h
	$(CC) -c replace_special_symbols.c -o replace_special_symbols.o

sort_by_latin_letters.o : sort_by_latin_letters.c sort_by_latin_letters.h read_text.h
	$(CC) -c sort_by_latin_letters.c -o sort_by_latin_letters.o

clean : 
	rm $(TARGET) *.o