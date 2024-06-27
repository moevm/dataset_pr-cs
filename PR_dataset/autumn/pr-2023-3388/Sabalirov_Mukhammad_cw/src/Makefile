all: main.o read.o ioroutine.o cyrillic.o dict.o special_symbols.o replace_to_binary.o remove_odd.o choice_answer.o free.o double.o
	gcc -std=c99 main.o read.o ioroutine.o cyrillic.o dict.o special_symbols.o replace_to_binary.o remove_odd.o choice_answer.o free.o double.o -o cw
main.o: main.c read.h
	gcc -c main.c
read.o: read.c structs.h read.h ioroutine.h
	gcc -c read.c
ioroutine.o: ioroutine.c ioroutine.h
	gcc -c ioroutine.c
cyrillic.o: cyrillic.c cyrillic.h structs.h dict.h ioroutine.h
	gcc -c cyrillic.c
dict.o: dict.c dict.h structs.h ioroutine.h
	gcc -c dict.c
special_symbols.o: special_symbols.c special_symbols.h structs.h ioroutine.h
	gcc -c special_symbols.c
replace_to_binary.o: replace_to_binary.c replace_to_binary.h  structs.h ioroutine.h dict.h
	gcc -c replace_to_binary.c
remove_odd.o: remove_odd.c remove_odd.h structs.h ioroutine.h
	gcc -c remove_odd.c
choice_answer.o: choice_answer.c choice_answer.h read.h structs.h ioroutine.h cyrillic.h dict.h special_symbols.h replace_to_binary.h remove_odd.h
	gcc -c choice_answer.c
free.o: free.c free.h structs.h
	gcc -c free.c
double.o: double.c double.h read.h structs.h ioroutine.h cyrillic.h dict.h special_symbols.h replace_to_binary.h remove_odd.h
	gcc -c double.c