all: main

main: menu.o answer.o convertTokenToInt.o userChoice.o readInput.o sum_before_and_after.o sum_between.o index_last_zero.o index_first_zero.o
	gcc -std=gnu99 -o menu menu.o answer.o convertTokenToInt.o userChoice.o readInput.o sum_before_and_after.o sum_between.o index_last_zero.o index_first_zero.o

main.o: menu.c menu.h answer.h convertTokenToInt.h userChoice.h readInput.h sum_before_and_after.h sum_between.h index_last_zero.h index_first_zero.h
	gcc -c menu.c -std=gnu99

answer.o: answer.c answer.h
	gcc -c answer.c -std=gnu99

convertTokenToInt.o: convertTokenToInt.c convertTokenToInt.h
	gcc -c convertTokenToInt.c -std=gnu99

userChoice.o: userChoice.c userChoice.h
	gcc -c userChoice.c -std=gnu99

readInput.o: readInput.c readInput.h
	gcc -c readInput.c -std=gnu99

sum_before_and_after.o: sum_before_and_after.c sum_before_and_after.h
	gcc -c sum_before_and_after.c -std=gnu99

sum_between.o: sum_between.c sum_between.h
	gcc -c sum_between.c -std=gnu99

index_last_zero.o: index_last_zero.c index_last_zero.h
	gcc -c index_last_zero.c -std=gnu99

index_first_zero.o: index_first_zero.c index_first_zero.h
	gcc -c index_first_zero.c -std=gnu99

clean:
	rm -r *.o menu -rf
