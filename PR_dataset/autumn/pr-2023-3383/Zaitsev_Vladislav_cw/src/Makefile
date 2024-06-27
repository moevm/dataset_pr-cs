all: cw clean

cw: main.o processtext.o Output.o readText.o Free.o deletesent.o Robin_to_Batman.o Sort_by_coma.o Delete_13.o First_vowel.o
	gcc main.o processtext.o Output.o readText.o Free.o deletesent.o Robin_to_Batman.o Sort_by_coma.o Delete_13.o First_vowel.o -o cw
main.o: main.c Output.h readText.h Free.h libs.h deletesent.h Robin_to_Batman.h Sort_by_coma.h Delete_13.h First_vowel.h libs.h
	gcc -c main.c
Output.o: readText.h Free.h libs.h deletesent.h Robin_to_Batman.h Sort_by_coma.h Delete_13.h First_vowel.h libs.h
	gcc -c Output.c
processtext.o: processtext.c processtext.h libs.h deletesent.h
	gcc -c processtext.c
readText.o: readText.c readText.h libs.h
	gcc -c readText.c
Free.o: Free.c libs.h Free.h
	gcc -c Free.c
deletesent.o: deletesent.c deletesent.h libs.h
	gcc -c deletesent.c
Robin_to_Batman.o: Robin_to_Batman.c Robin_to_Batman.h libs.h
	gcc -c Robin_to_Batman.c
Sort_by_coma.o: Sort_by_coma.c Sort_by_coma.h libs.h
	gcc -c Sort_by_coma.c
Delete_13.o: Delete_13.c Delete_13.h libs.h deletesent.h
	gcc -c Delete_13.c
First_vowel.o: First_vowel.c First_vowel.h libs.h deletesent.h
	gcc -c First_vowel.c
clean: 
	rm -rf *.o main
