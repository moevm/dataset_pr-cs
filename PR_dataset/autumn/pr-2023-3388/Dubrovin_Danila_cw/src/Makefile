all: cw clean

cw: main.o supporting_functions.o data_processing.o general_functions.o output_functions.o
	gcc main.o supporting_functions.o data_processing.o general_functions.o output_functions.o -o cw

main.o: main.c supporting_functions.o data_processing.o general_functions.o output_functions.o data_processing.h structs_libraries.h general_functions.h output_functions.h
	gcc -c main.c

supporting_functions.o: supporting_functions.c structs_libraries.h
	gcc -c supporting_functions.c

data_processing.o: data_processing.c structs_libraries.h supporting_functions.h
	gcc -c data_processing.c

general_functions.o: general_functions.c structs_libraries.h supporting_functions.h
	gcc -c general_functions.c

output_functions.o: output_functions.c structs_libraries.h data_processing.h general_functions.h
	gcc -c output_functions.c

clean:
	find . -name "*.o" ! -name "cw.o" -type f -exec rm -f {} +
