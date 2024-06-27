CC=gcc
CFLAGS=-std=c99

all: menu

menu: enter_array_values.o index_first_even.o index_last_odd.o sum_before_even_and_after_odd.o sum_between_even_odd.o menu.o
	${CC} $^ -o $@ ${CFLAGS}

enter_array_values.o: enter_array_values.c enter_array_values.h
	${CC} -c $< ${CFLAGS}

index_first_even.o: index_first_even.c index_first_even.h
	${CC} -c $< ${CFLAGS}

index_last_odd.o: index_last_odd.c index_last_odd.h
	${CC} -c $< ${CFLAGS}

sum_before_even_and_after_odd.o: sum_before_even_and_after_odd.c sum_before_even_and_after_odd.h index_first_even.h index_last_odd.h
	${CC} -c $< ${CFLAGS}

sum_between_even_odd.o: sum_between_even_odd.c sum_between_even_odd.h index_first_even.h index_last_odd.h
	${CC} -c $< ${CFLAGS}

menu.o: menu.c enter_array_values.h index_first_even.h index_last_odd.h sum_before_even_and_after_odd.h sum_between_even_odd.h
	${CC} -c $< ${CFLAGS}

clean:
	rm *.o
