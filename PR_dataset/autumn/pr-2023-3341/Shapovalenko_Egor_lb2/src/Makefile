all: menu.o input.o buffer_processing.o command_processing.o abs_max.o abs_min.o diff.o sum.o print.o
        gcc menu.o input.o buffer_processing.o command_processing.o abs_max.o abs_min.o diff.o sum.o print.o -o menu
menu.o: menu.c input.h buffer_processing.h command_processing.h
        gcc -c menu.c
input.o: input.c input.h
        gcc -c input.c
buffer_processing.o: buffer_processing.c buffer_processing.h
        gcc -c buffer_processing.c
command_processing.o: command_processing.c command_processing.h abs_max.h abs_min.h diff.h sum.h print.h
        gcc -c command_processing.c
abs_max.o: abs_max.c abs_max.h
        gcc -c -std=c99 abs_max.c
abs_min.o: abs_min.c abs_min.h
        gcc -c -std=c99 abs_min.c
diff.o: diff.c diff.h abs_max.h abs_min.h
        gcc -c diff.c
sum.o: sum.c sum.h abs_max.h
        gcc -c -std=c99 sum.c
print.o: print.c print.h
		gcc -c print.c
clean:
        rm -rf *.o menu