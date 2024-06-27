all: main.o read.o select_func.o all_translitiration.o all_bin_text.o all_special_sym.o delete_odd.o other_stuff.o
	gcc main.o read.o select_func.o all_translitiration.o all_bin_text.o all_special_sym.o delete_odd.o other_stuff.o -o cw
main.o: main.c read.h
	gcc -c main.c
other_stuff.o: other_stuff.c other_stuff.h
	gcc -c other_stuff.c
read.o: read.c structs.h read.h other_stuff.h
	gcc -c read.c
select_func.o: select_func.c select_func.h structs.h read.h other_stuff.h
	gcc -c select_func.c
all_translitiration.o: all_translitiration.c all_translitiration.h structs.h other_stuff.h
	gcc -c all_translitiration.c
all_bin_text.o: all_bin_text.c all_bin_text.h structs.h other_stuff.h
	gcc -c all_bin_text.c
all_special_sym.o: all_special_sym.c all_special_sym.h structs.h other_stuff.h
	gcc -c all_special_sym.c
delete_odd.o: delete_odd.c delete_odd.h structs.h other_stuff.h
	gcc -c delete_odd.c



