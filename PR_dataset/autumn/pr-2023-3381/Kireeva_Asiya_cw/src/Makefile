all: cw
cw: main.o get_text.o zero_func.o first_func.o second_func.o third_func.o fourth_func.o fifth_func.o ninth_func.o free_space.o
	gcc main.o get_text.o zero_func.o first_func.o second_func.o third_func.o fourth_func.o fifth_func.o ninth_func.o free_space.o -lm -o cw
main.o: main.c main.h
	gcc -c -g main.c
get_text.o: get_text.c main.h
	gcc -c -g get_text.c
zero_func.o: zero_func.c main.h
	gcc -c -g zero_func.c
first_func.o: first_func.c main.h
	gcc -c -g first_func.c
second_func.o: second_func.c main.h
	gcc -c -g second_func.c
third_func.o: third_func.c main.h
	gcc -c -g third_func.c
fourth_func.o: fourth_func.c main.h
	gcc -c -g fourth_func.c
fifth_func.o: fifth_func.c main.h
	gcc -c -g fifth_func.c
ninth_func.o: ninth_func.c main.h
	gcc -c -g ninth_func.c
free_space.o: free_space.c main.h
	gcc -c -g free_space.c
clean:
	rm -rf *.o cw