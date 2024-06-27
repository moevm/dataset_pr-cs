all : cw
main.o : main.c
	gcc -std=gnu99 -c main.c
check_mid_num.o : check_mid_num.c
	gcc -std=gnu99 -c check_mid_num.c
len_third.o : len_third.c
	gcc -std=gnu99 -c len_third.c
cmp.o : cmp.c
	gcc -std=gnu99 -c cmp.c
cmp_sents.o : cmp_sents.c
	gcc -std=gnu99 -c cmp_sents.c
description.o : description.c
	gcc -std=gnu99 -c description.c
double_en.o : double_en.c
	gcc -std=gnu99 -c double_en.c
error_check.o : error_check.c
	gcc -std=gnu99 -c error_check.c
function_select.o : function_select.c
	gcc -std=gnu99 -c function_select.c
get_second_word.o : get_second_word.c
	gcc -std=gnu99 -c get_second_word.c
get_separators.o : get_separators.c
	gcc -std=gnu99 -c get_separators.c
structures.o : structures.c
	gcc -std=gnu99 -c structures.c
symbols_changer.o : symbols_changer.c
	gcc -std=gnu99 -c symbols_changer.c
word_replacement.o : word_replacement.c
	gcc -std=gnu99 -c word_replacement.c
word_symbol_changer.o : word_symbol_changer.c
	gcc -std=gnu99 -c word_symbol_changer.c
num_middle.o : num_middle.c
	gcc -std=gnu99 -c num_middle.c
checking.o : checking.c
	gcc -std=gnu99 -c checking.c
func9.o : func9.c
	gcc -std=gnu99 -c func9.c
cw : main.o len_third.o get_separators.o get_second_word.o function_select.o error_check.o double_en.o description.o cmp_sents.o cmp.o check_mid_num.o structures.o symbols_changer.o word_replacement.o word_symbol_changer.o num_middle.o checking.o func9.o
	gcc main.o len_third.o get_separators.o get_second_word.o function_select.o error_check.o double_en.o description.o cmp_sents.o cmp.o check_mid_num.o structures.o symbols_changer.o word_replacement.o word_symbol_changer.o num_middle.o checking.o func9.o -o cw
	rm *.o