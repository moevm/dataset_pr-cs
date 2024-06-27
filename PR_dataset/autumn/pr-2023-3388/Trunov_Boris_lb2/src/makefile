all: menu.o data_reading.o index_first_negative.o index_last_negative.o print_solve.o multi_between_negative.o multi_before_and_after_negative.o
	gcc menu.o data_reading.o index_first_negative.o index_last_negative.o print_solve.o multi_between_negative.o multi_before_and_after_negative.o -o menu
menu.o: menu.c data_reading.h print_solve.h
	gcc -c menu.c
data_reading.o: data_reading.c data_reading.h
	gcc -c data_reading.c
print_solve.o: print_solve.c print_solve.h index_first_negative.h index_last_negative.h
	gcc -c print_solve.c
index_first_negative.o: index_first_negative.c index_first_negative.h
	gcc -c index_first_negative.c
index_last_negative.o: index_last_negative.c index_last_negative.h
	gcc -c index_last_negative.c
multi_between_negative.o: multi_between_negative.c multi_between_negative.h index_first_negative.h index_last_negative.h
	gcc -c multi_between_negative.c
multi_before_and_after_negative.o: multi_before_and_after_negative.c multi_before_and_after_negative.h index_first_negative.h index_last_negative.h
	gcc -c multi_before_and_after_negative.c
clean:
	rm -f *.o
	rm -f *.out
