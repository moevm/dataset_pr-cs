menu: menu.o index_first_zero.o index_last_zero.o sum_between.o sum_before_and_after.o
        gcc -std=c99  menu.o index_first_zero.o index_last_zero.o sum_between.o sum_before_and_after.o  -o menu

index_first_zero.o: index_first_zero.c index_first_zero.h
        gcc -std=c99 -c index_first_zero.c -o index_first_zero.o
index_last_zero.o: index_last_zero.c index_last_zero.h
        gcc -std=c99 -c index_last_zero.c -o index_last_zero.o

sum_between_zero.o: sum_between.c sum_between.h index_first_zero.h index_last_zero.h
        gcc -std=c99 -c sum_between.c -o sum_between.o

sum_before_and_after.o: sum_before_and_after.c sum_before_and_after.h index_first_zero.h index_last_zero.h
        gcc -std=c99 -c sum_before_and_after.c -o sum_before_and_after.o

menu.o: menu.c index_first_zero.h index_last_zero.h sum_between.h sum_before_and_after.h
        gcc -std=c99 -c menu.c -o menu.o



