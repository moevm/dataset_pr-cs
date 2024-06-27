all: menu.o max.o min.o diff.o sum.o work_with_data.o get_data.o
	gcc menu.o max.o min.o diff.o sum.o work_with_data.o get_data.o -o menu
menu.o: menu.c max.h
	gcc -c -std=c99 menu.c max.h min.h diff.h sum.h work_with_data.h get_data.h
max.o: max.h max.c
	gcc -c -std=c99 max.h max.c
min.o: min.h min.c
	gcc -c -std=c99 min.h min.c
diff.o: diff.h diff.c
	gcc -c -std=c99 diff.h diff.c max.h min.h
sum.o: sum.h sum.c
	gcc -c -std=c99 sum.c sum.h min.h
work_with_data.o: work_with_data.h work_with_data.c
	gcc -c -std=c99 work_with_data.h work_with_data.c sum.h min.h diff.h max.h
get_data.o: get_data.h get_data.c
	gcc -c -std=c99 get_data.h get_data.c
