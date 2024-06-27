all: main clean

main: main.o func_cw.o freedom.o func_translit.o func_sort_sym.o func_repl_digit.o func_odd_del.o func_obr_text.o func_vvod_text.o func_out.o
	gcc main.o func_cw.o freedom.o func_translit.o func_sort_sym.o func_repl_digit.o func_odd_del.o func_out.o func_obr_text.o func_vvod_text.o -o cw

main.o: main.c func_cw.h freedom.h func_translit.h func_sort_sym.h func_repl_digit.h func_odd_del.h func_out.h func_vvod_text.h func_obr_text.h struct.h

func_vvod_text.o: func_vvod_text.c struct.h
	gcc -c func_vvod_text.c

func_obr_text.o: func_obr_text.c struct.h
	gcc -c func_obr_text.c

func_translit.o: func_translit.c struct.h
	gcc -c func_translit.c

func_sort_sym.o: func_sort_sym.c struct.h
	gcc -c func_sort_sym.c

func_repl_digit.o: func_repl_digit.c struct.h
	gcc -c func_repl_digit.c

func_odd_del.o: func_odd_del.c struct.h
	gcc -c func_odd_del.c

func_out.o: func_out.c struct.h freedom.h
	gcc -c func_out.c

freedom.o: freedom.c struct.h
	gcc -c freedom.c

func_cw.o: func_cw.c struct.h
	gcc -c func_cw.c

clean:
	rm -rf *.o main