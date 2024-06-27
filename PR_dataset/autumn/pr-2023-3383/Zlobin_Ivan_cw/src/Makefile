all: cw
cw: main.o input.o output.o cleaning.o delete_words.o func_description.o len_of_word.o middle_len_sort.o small_end_len_sort.o word_mask.o mask_input.o func.o
	gcc main.o input.o output.o cleaning.o delete_words.o func_description.o len_of_word.o middle_len_sort.o small_end_len_sort.o word_mask.o mask_input.o func.o -o cw
main.o: main.c cleaning.h delete_words.h func_description.h input.h len_of_word.h main_lib.h middle_len_sort.h output.h small_end_len_sort.h word_mask.h mask_input.h
	gcc -c -g main.c
cleaning.o: cleaning.c main_lib.h
	gcc -c -g cleaning.c
delete_words.o: delete_words.c main_lib.h len_of_word.h
	gcc -c -g delete_words.c
func_description.o: func_description.c main_lib.h
	gcc -c -g func_description.c 
input.o: input.c main_lib.h 
	gcc -c -g input.c 
len_of_word.o: len_of_word.c main_lib.h
	gcc -c -g len_of_word.c 
middle_len_sort.o: middle_len_sort.c main_lib.h len_of_word.h
	gcc -c -g middle_len_sort.c 
output.o: output.c main_lib.h
	gcc -c -g output.c
small_end_len_sort.o: small_end_len_sort.c main_lib.h len_of_word.h
	gcc -c -g small_end_len_sort.c 
word_mask.o: word_mask.c main_lib.h 
	gcc -c -g word_mask.c
mask_input.o: mask_input.h main_lib.h
	gcc -c -g mask_input.c
func.o: func.c main_lib.h len_of_word.h
	gcc -c -g func.c
clean:
	rm -rf *.o
	rm -rf cw
