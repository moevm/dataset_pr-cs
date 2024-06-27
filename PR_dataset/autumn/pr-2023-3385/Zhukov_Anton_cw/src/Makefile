all: main.o func1.o func2.o func3.o func4.o func5.o func9.o print_text.o free_text.o choose_number.o input_text.o
	gcc main.o func1.o func2.o func3.o func4.o func5.o func9.o print_text.o free_text.o choose_number.o input_text.o -o cw
main.o: main.c func1.h func2.h func3.h func4.h func5.h print_text.h free_text.h choose_number.h input_text.h
	gcc -c main.c
func1.o: func1.c func1.h
	gcc -c func1.c
func2.o: func2.c func2.h print_text.h
	gcc -c func2.c
func3.o: func3.c func3.h print_text.h free_text.h
	gcc -c func3.c
func4.o: func4.c func4.h print_text.h
	gcc -c func4.c
func5.o: func5.c func5.h
	gcc -c func5.c
func9.o: func9.c func9.h
	gcc -c func9.c
print_text.o: print_text.c print_text.h
	gcc -c print_text.c
free_text.o: free_text.c free_text.h
	gcc -c free_text.c
choose_number.o: choose_number.c choose_number.h
	gcc -c choose_number.c
input_text.o: input_text.c input_text.h
	gcc -c input_text.c
clean:
	rm -rf *.o cw
