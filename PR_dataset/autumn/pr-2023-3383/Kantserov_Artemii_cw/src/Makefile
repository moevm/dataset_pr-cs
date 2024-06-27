all : main clean
main : main.o input.o same_year_and_month.o my_lib.o del_19age.o certificate.o put.o min_max.o sort_min.o
	gcc main.o input.o same_year_and_month.o my_lib.o del_19age.o certificate.o min_max.o sort_min.o put.o -o cw
main.o : main.c my_lib.h input.h same_year_and_month.h sort_min.h del_19age.h certificate.h struct.h
	gcc -c main.c
my_lib.o : my_lib.c my_lib.h struct.h
	gcc -c my_lib.c
input.o : input.c input.h my_lib.h struct.h
	gcc -c input.c
same_year_and_month.o : same_year_and_month.c same_year_and_month.h struct.h
	gcc -c same_year_and_month.c
del_19age.o : del_19age.c del_19age.h my_lib.h struct.h
	gcc -c del_19age.c
certificate.o : certificate.c certificate.h
	gcc -c certificate.c
min_max.o : min_max.c min_max.h my_lib.h struct.h
	gcc -c min_max.c
sort_min.o : sort_min.c sort_min.h my_lib.h struct.h
	gcc -c sort_min.c
put.o : put.c put.h struct.h my_lib.h
	gcc -c put.c
clean :
	rm -rf *.o main