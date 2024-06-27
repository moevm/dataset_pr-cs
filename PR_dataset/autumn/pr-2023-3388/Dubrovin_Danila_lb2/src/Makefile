all: menu.o max.o min.o diff.o sum.o show_answer.o read_array.o choose_answer.o
	gcc menu.o max.o min.o diff.o sum.o show_answer.o read_array.o choose_answer.o -o menu
	
menu.o: menu.c max.h min.h diff.h sum.h show_answer.h read_array.h choose_answer.h
	gcc -c -std=c99 menu.c
	
max.o: max.c max.h
	gcc -c -std=c99 max.c
	
min.o: min.c min.h
	gcc -c -std=c99 min.c
	
diff.o: diff.c max.h min.h diff.h
	gcc -c -std=c99 diff.c
	
sum.o: sum.c sum.h
	gcc -c -std=c99 sum.c
	
show_answer.o: show_answer.c show_answer.h
	gcc -c -std=c99 show_answer.c
	
read_array.o: read_array.c read_array.h
	gcc -c -std=c99 read_array.c
	
choose_answer.o: choose_answer.c max.h min.h diff.h sum.h show_answer.h choose_answer.h
	gcc -c  -std=c99 choose_answer.c
	
clean:
	rm -f *.o menu:
