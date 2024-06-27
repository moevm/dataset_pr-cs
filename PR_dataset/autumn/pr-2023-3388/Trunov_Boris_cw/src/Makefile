all: main.o welcome.o action_selection.o failure.o help.o read_text.o add_smile.o count_length_words.o set_unic.o delete_last_upper_char.o output_text.o move_words.o free_memory.o
	gcc -std=c99 main.o welcome.o action_selection.o failure.o help.o read_text.o add_smile.o set_unic.o count_length_words.o delete_last_upper_char.o output_text.o move_words.o free_memory.o -o cw
main.o: main.c welcome.h action_selection.h
	gcc -c main.c
welcome.o: welcome.c welcome.h
	gcc -c welcome.c
action_selection.o: action_selection.c action_selection.h config_action_selection.h
	gcc -c action_selection.c
failure.o: failure.c failure.h
	gcc -c failure.c
help.o: help.c help.h
	gcc -c help.c
read_text.o: read_text.c read_text.h
	gcc -c read_text.c
output_text.o: output_text.c output_text.h
	gcc -c output_text.c
free_memory.o:	free_memory.c free_memory.h
	gcc -c free_memory.c
move_words.o: move_words.c move_words.h
	gcc -c move_words.c
delete_last_upper_char.o: delete_last_upper_char.c delete_last_upper_char.h
	gcc -c delete_last_upper_char.c
set_unic.o:	set_unic.c set_unic.h
	gcc -c set_unic.c
count_length_words.o: count_length_words.c count_length_words.h
	gcc -c count_length_words.c
add_smile.o: add_smile.h add_smile.c
	gcc -c add_smile.c
clean:
	rm -f *.o
	rm -f cw
