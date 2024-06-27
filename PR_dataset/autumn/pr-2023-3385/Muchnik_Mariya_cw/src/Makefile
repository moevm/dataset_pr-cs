all: cw

cw: main.o print_error.o print_help.o get_text.o print_text.o get_minutes.o sort_sentences.o replace_symbols.o delete_sentences.o check_words.o free_all.o
	gcc main.o print_error.o print_help.o get_text.o print_text.o get_minutes.o sort_sentences.o replace_symbols.o delete_sentences.o check_words.o free_all.o -o cw && ./cw

main.o: main.c get_text.h free_all.h
	gcc -c main.c

print_error.o: print_error.c print_error.h
	gcc -c print_error.c

print_help.o: print_help.c print_help.h
	gcc -c print_help.c

get_text.o: get_text.c get_text.h print_error.h free_all.h
	gcc -c get_text.c

print_text.o: print_text.c print_text.h
	gcc -c print_text.c

get_minutes.o: get_minutes.c get_minutes.h
	gcc -c get_minutes.c

sort_sentences.o: sort_sentences.c sort_sentences.h
	gcc -c sort_sentences.c

replace_symbols.o: replace_symbols.c replace_symbols.h print_error.h free_all.h
	gcc -c replace_symbols.c

delete_sentences.o: delete_sentences.c delete_sentences.h
	gcc -c delete_sentences.c

check_words.o: check_words.c check_words.h
	gcc -c check_words.c

free_all.o: free_all.c free_all.h
	gcc -c free_all.c

clean:
	rm -f ./*.o cw
