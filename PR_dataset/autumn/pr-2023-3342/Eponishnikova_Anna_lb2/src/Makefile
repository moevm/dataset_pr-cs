all:menu.o abs_max.o abs_min.o diff.o sum.o answer.o input_array.o
        gcc menu.o abs_max.o abs_min.o diff.o sum.o answer.o input_array.o -o menu
menu.o: menu.c answer.h input_array.h
        gcc -c  -std=c99 menu.c
abs_max.o: abs_max.h abs_max.c
        gcc -c  -std=c99 abs_max.c
abs_min.o: abs_min.h abs_min.c
        gcc -c  -std=c99 abs_min.c
diff.o: diff.h abs_min.h abs_max.h diff.c
        gcc -c  -std=c99 diff.c
sum.o: sum.h sum.c abs_max.h
        gcc -c  -std=c99 sum.o
input_array.o: input_array.c input_array.h
        gcc -c  -std=c99 input_array.c
answer.o: answer.c answer.h abs_max.h abs_min.h diff.h sum.h
        gcc -c  -std=c99 answer.c