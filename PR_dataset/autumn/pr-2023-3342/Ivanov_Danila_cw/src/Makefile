CC=gcc
CFLAGS=-c -std=c11

all: main.o reading.o delete.o memory.o function_sum_of_minutes.o function_sort.o function_of_replace_symbols.o function_of_delete_sentences.o reference.o function_print_some_sentences.o
	$(CC) main.o function_print_some_sentences.o reading.o delete.o memory.o function_sum_of_minutes.o function_sort.o function_of_replace_symbols.o function_of_delete_sentences.o reference.o -o cw

main.o: main.c reading.h
	$(CC) $(CFLAGS)  main.c

reading.o: reading.h
	$(CC) $(CFLAGS) reading.c

delete.o: delete.h
	$(CC) $(CFLAGS) delete.c

memory.o: memory.h
	$(CC) $(CFLAGS) memory.c

function_sum_of_minutes.o: function_sum_of_minutes.h
	$(CC) $(CFLAGS) function_sum_of_minutes.c

function_sort.o: function_sort.h
	$(CC) $(CFLAGS) function_sort.c

function_of_replace_symbols.o: function_of_replace_symbols.h
	$(CC) $(CFLAGS) function_of_replace_symbols.c

function_of_delete_sentences.o: function_of_delete_sentences.h
	$(CC) $(CFLAGS) function_of_delete_sentences.c

function_print_some_sentences.o: function_print_some_sentences.h
	$(CC) $(CFLAGS) function_print_some_sentences.c

reference.o: reference.h
	$(CC) $(CFLAGS) reference.c

clean:
	rm -rf *.o
	rm -rf cw.exe
	rm -rf cw