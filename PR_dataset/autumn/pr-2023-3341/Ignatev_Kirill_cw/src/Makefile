all: cw.o input.o output.o only_num.o del_sent_by_word.o replace_digits_with_words.o sort_strings_by_uppercase_count.o allocator.o remove_duplicates.o errors.o defence.o
	gcc cw.o input.o output.o only_num.o del_sent_by_word.o replace_digits_with_words.o sort_strings_by_uppercase_count.o allocator.o remove_duplicates.o errors.o defence.o -o cw
cw.o:
	gcc -c core/cw.c
input.o:
	gcc -c core/input.c
output.o:
	gcc -c core/output.c
only_num.o:
	gcc -c core/only_num.c
del_sent_by_word.o:
	gcc -c core/del_sent_by_word.c
replace_digits_with_words.o:
	gcc -c core/replace_digits_with_words.c
sort_strings_by_uppercase_count.o:
	gcc -c core/sort_strings_by_uppercase_count.c
allocator.o:
	gcc -c core/allocator.c
remove_duplicates.o:
	gcc -c core/remove_duplicates.c
errors.o:
	gcc -c core/errors.c
defence.o:
	gcc -c core/defence.c
clean:
	rm *.o cw
