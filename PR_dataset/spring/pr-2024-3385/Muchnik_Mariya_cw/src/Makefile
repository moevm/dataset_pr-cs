all: cw

cw: main.o bmp_rw.o print_info.o print_help.o error_handler.o func_replace_color.o func_rgb_filter.o func_split.o extra_func.o
	gcc main.o bmp_rw.o print_info.o print_help.o error_handler.o func_replace_color.o func_rgb_filter.o func_split.o extra_func.o -o cw

main.o: main.c bmp_rw.h
	gcc -c main.c

bmp_rw.o: bmp_rw.c bmp_rw.h
	gcc -c bmp_rw.c

print_info.o: print_info.c print_info.h
	gcc -c print_info.c

print_help.o: print_help.c print_help.h
	gcc -c print_help.c

error_handler.o: error_handler.c error_handler.h
	gcc -c error_handler.c

func_replace_color.o: func_replace_color.c func_replace_color.h
	gcc -c func_replace_color.c

func_rgb_filter.o: func_rgb_filter.c func_rgb_filter.h
	gcc -c func_rgb_filter.c

func_split.o: func_split.c func_split.h
	gcc -c func_split.c	

extra_func.o: extra_func.c extra_func.h 
	gcc -c extra_func.c

clean:
	rm -f ./*.o cw