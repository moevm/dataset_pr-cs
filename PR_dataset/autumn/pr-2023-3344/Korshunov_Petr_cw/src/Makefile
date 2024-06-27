CC = gcc
FLAGS = -std=c99

all: menu.o text_processing.o input.o output.o del_sents_with_spec_symb.o del_uppercase.o get_time_substr.o sort_cyrillic.o replace_if_bigger.o
	$(CC) $(FLAGS) -o cw -D_GNU_SOURCE menu.o text_processing.o input.o output.o del_sents_with_spec_symb.o del_uppercase.o get_time_substr.o sort_cyrillic.o replace_if_bigger.o

menu.o: menu.c structs.h input.h output.h text_processing.h del_sents_with_spec_symb.h del_uppercase.h get_time_substr.h sort_cyrillic.h
	$(CC) $(FLAGS) -c menu.c

text_processing.o: text_processing.c structs.h
	$(CC) $(FLAGS) -c text_processing.c

input.o: input.c structs.h text_processing.h
	$(CC) -$(FLAGS) -c input.c

output.o: output.c structs.h
	$(CC) $(FLAGS) -c output.c

del_sents_with_spec_symb.o: del_sents_with_spec_symb.c structs.h
	$(CC) $(FLAGS) -c del_sents_with_spec_symb.c

del_uppercase.o: del_uppercase.c structs.h
	$(CC) $(FLAGS) -c del_uppercase.c

get_time_substr.o: get_time_substr.c structs.h
	$(CC) $(FLAGS) -D_GNU_SOURCE -c get_time_substr.c 

replace_if_bigger.o: replace_if_bigger.c structs.h
	$(CC) $(FLAGS) -c replace_if_bigger.c

sort_cyrillic.o: sort_cyrillic.c structs.h
	$(CC) $(FLAGS) -c sort_cyrillic.c

clean:
	rm *.o