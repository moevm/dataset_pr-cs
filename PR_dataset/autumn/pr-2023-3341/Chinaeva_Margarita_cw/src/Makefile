all: checking_symbol.o delete_cyrillic_latin.o errors.o first_info.o free_memory.o input.o list_option.o main.o option.o output.o palindrome.o preprocessing.o replace_special_symbol.o sort_latin.o
	gcc checking_symbol.o delete_cyrillic_latin.o errors.o first_info.o free_memory.o input.o list_option.o main.o option.o output.o palindrome.o preprocessing.o replace_special_symbol.o sort_latin.o -o cw

checking_symbol.o: checking_symbol.c
	gcc -c checking_symbol.c

delete_cyrillic_latin.o: delete_cyrillic_latin.c
	gcc -c delete_cyrillic_latin.c
	
errors.o: errors.c
	gcc -c errors.c
	
first_info.o: first_info.c
	gcc -c first_info.c

free_memory.o: free_memory.c
	gcc -c free_memory.c
	
input.o: input.c
	gcc -c input.c

list_option.o: list_option.c
	gcc -c list_option.c

main.o: main.c
	gcc -c main.c

option.o: option.c
	gcc -c option.c

output.o: output.c
	gcc -c output.c

palindrome.o: palindrome.c
	gcc -c palindrome.c

preprocessing.o: preprocessing.c
	gcc -c preprocessing.c

sort_latin.o: sort_latin.c
	gcc -c sort_latin.c

replace_special_symbol.o: replace_special_symbol.c
	gcc -c replace_special_symbol.c

clean: 
	rm -rf *.o cw
