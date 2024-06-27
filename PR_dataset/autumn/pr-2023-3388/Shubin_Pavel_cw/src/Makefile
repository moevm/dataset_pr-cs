all: cw clean

cw: main.o output_function.o support_functions.o user_functions.o text_reading.o
	gcc -g main.o output_function.o support_functions.o user_functions.o text_reading.o -o cw 

main.o: main.c output_function.o support_functions.o user_functions.o text_reading.o output_function.h user_functions.h text_reading.h structs_libraries.h
	gcc -g -c main.c

output_function.o: output_function.c output_function.h structs_libraries.h user_functions.h support_functions.h
	gcc -g -c output_function.c

support_functions.o: support_functions.c support_functions.h structs_libraries.h
	gcc -g -c support_functions.c

user_functions.o: user_functions.c user_functions.h structs_libraries.h support_functions.h
	gcc -g -c user_functions.c

text_reading.o: text_reading.c text_reading.h structs_libraries.h
	gcc -g -c text_reading.c

clean:
	rm -f *.o
