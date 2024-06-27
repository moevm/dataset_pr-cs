CFLAG = -std=c99


all: main.o foo.o printF_text.o input.o text_to_words.o find_middle_time_and_translate.o compare.o find_dates.o delete_same_words_sent.o is_happened.o
	gcc $(CFLAG) *.o -o cw

main.o: main.c foo.h printF_text.h input.h text_to_words.h find_middle_time_and_translate.h compare.h find_dates.h delete_same_words_sent.h is_happened.h base_library.h
	gcc -c $(CFLAG) main.c

foo.o: foo.c foo.h base_library.h
	gcc -c $(CFLAG) foo.c
	
printF_text.o: printF_text.c printF_text.h base_library.h
	gcc -c $(CFLAG) printF_text.c

input.o: input.c input.h base_library.h
	gcc -c $(CFLAG) input.c

text_to_words.o: text_to_words.c text_to_words.h base_library.h
	gcc -c $(CFLAG) text_to_words.c

find_middle_time_and_translate.o: find_middle_time_and_translate.c find_middle_time_and_translate.h base_library.h
	gcc -c $(CFLAG) find_middle_time_and_translate.c

compare.o: compare.c compare.h base_library.h
	gcc -c $(CFLAG) compare.c

find_dates.o: find_dates.c find_dates.h base_library.h
	gcc -c $(CFLAG) find_dates.c

delete_same_words_sent.o: delete_same_words_sent.c delete_same_words_sent.h base_library.h
	gcc -c $(CFLAG) delete_same_words_sent.c

is_happened.o: is_happened.c is_happened.h base_library.h
	gcc -c $(CFLAG) is_happened.c
	
clean:
	rm -f *.o cw

run :
	./cw
