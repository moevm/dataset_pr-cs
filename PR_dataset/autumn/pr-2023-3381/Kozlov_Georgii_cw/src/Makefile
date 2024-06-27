all: main.o get_text.o modify_text.o  time_function.o
	gcc main.o get_text.o modify_text.o time_function.o -o cw

main.o: main.c headers.h struct_define.h
	gcc -c main.c

get_text.o: get_text.c struct_define.h
	gcc -c get_text.c

modify_text.o: modify_text.c headers.h
	gcc -c modify_text.c

time_function.o: time_function.c
	gcc -c time_function.c
	
clean:
	rm -rf *.o cw
