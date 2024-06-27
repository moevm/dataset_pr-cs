FLAG = -std=c99

all: main.o fill_and_firstprocc_structure.o switch_first_word.o switch_first_word.o cmp.o print_colourwords.o delete_repeatChar.o print_options.o print_structure.o switchwords.o
	gcc $(FLAG) -o cw *.o

main.o: main.c fill_and_firstprocc_structure.h switch_first_word.h cmp.h print_colourwords.h delete_repeatChar.h print_options.h print_structure.h switchwords.h structures.h
	gcc -c $(FLAG) main.c

fill_and_firstprocc_structure.o: fill_and_firstprocc_structure.c fill_and_firstprocc_structure.h structures.h
	gcc -c $(FLAG) fill_and_firstprocc_structure.c

switch_first_word.o: switch_first_word.c switch_first_word.h structures.h
	gcc -c $(FLAG) switch_first_word.c 

cmp.o: cmp.c cmp.h structures.h
	gcc -c $(FLAG) cmp.c

print_colourwords.o: print_colourwords.c print_colourwords.h structures.h
	gcc -c $(FLAG) print_colourwords.c

delete_repeatChar.o: delete_repeatChar.c delete_repeatChar.h structures.h
	gcc -c $(FLAG) delete_repeatChar.c

print_options.o: print_options.c print_options.h 
	gcc -c $(FLAG) print_options.c

print_structure.o: print_structure.c print_structure.h structures.h
	gcc -c $(FLAG) print_structure.c

switchwords.o: switchwords.c switchwords.h structures.h
	gcc -c $(FLAG) switchwords.c

clean:
	rm -f *.o cw
