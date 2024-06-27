all: menu.o DataReading.o index_first_zero.o index_last_zero.o sumAbs.o sum_between.o sum_before_and_after.o writeAnswer.o choiseAnswer.o
	gcc menu.o DataReading.o index_first_zero.o index_last_zero.o sumAbs.o sum_between.o sum_before_and_after.o writeAnswer.o choiseAnswer.o -o menu
menu.o: menu.c choiseAnswer.h DataReading.h
	gcc -c -std=c99 menu.c
DataReading.o: DataReading.c DataReading.h
	gcc -c -std=c99 DataReading.c
index_first_zero.o: index_first_zero.c index_first_zero.h
	gcc -c -std=c99 index_first_zero.c
index_last_zero.o: index_last_zero.c index_last_zero.h
	gcc -c -std=c99 index_last_zero.c
sumAbs.o: sumAbs.c sumAbs.h
	gcc -c -std=c99 sumAbs.c
sum_between.o: sum_between.c sumAbs.h index_first_zero.h index_last_zero.h sum_between.h
	gcc -c -std=c99 sum_between.c
sum_before_and_after.o: sum_before_and_after.c sumAbs.h index_first_zero.h index_last_zero.h sum_before_and_after.h
	gcc -c -std=c99 sum_before_and_after.c
writeAnswer.o: writeAnswer.c writeAnswer.h
	gcc -c -std=c99 writeAnswer.c	
choiseAnswer.o: choiseAnswer.c writeAnswer.h choiseAnswer.h
	gcc -c -std=c99 choiseAnswer.c
