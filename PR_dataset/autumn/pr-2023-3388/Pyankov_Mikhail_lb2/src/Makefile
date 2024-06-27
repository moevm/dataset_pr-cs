all: menu.o input_key_data.o input_array_data.o index_first_negative.o index_last_negative.o input_data_checking.o multi_between_negative.o multi_before_and_after_negative.o switch_function.o
	gcc -std=c99 menu.o input_key_data.o input_array_data.o index_first_negative.o index_last_negative.o input_data_checking.o multi_between_negative.o multi_before_and_after_negative.o switch_function.o -o menu

main.o: menu.c input_key_data.h input_array_data.h index_first_negative.h index_last_negative.h multi_between_negative.h multi_before_and_after_negative.h switch_function.h
	gcc -c -std=c99 menu.c

input_key_data.o: input_key_data.c input_key_data.h
	gcc -c -std=c99 input_key_data.c

input_array_data.o: input_array_data.c input_array_data.h
	gcc -c -std=c99 input_array_data.c

index_first_negative.o: index_first_negative.c index_first_negative.h
	gcc -c -std=c99 index_first_negative.c

index_last_negative.o: index_last_negative.c index_last_negative.h
	gcc -c -std=c99 index_last_negative.c

input_data_checking.o: input_data_checking.c input_data_checking.h
	gcc -c -std=c99 input_data_checking.c

multi_between_negative.o: multi_between_negative.c index_first_negative.h index_last_negative.h multi_between_negative.h
	gcc -c -std=c99 multi_between_negative.c

multi_before_and_after_negative.o: multi_before_and_after_negative.c index_first_negative.h index_last_negative.h multi_before_and_after_negative.h
	gcc -c -std=c99 multi_before_and_after_negative.c

switch_function.o: switch_function.c index_first_negative.h index_last_negative.h multi_between_negative.h multi_before_and_after_negative.h switch_function.h
	gcc -c -std=c99 switch_function.c

