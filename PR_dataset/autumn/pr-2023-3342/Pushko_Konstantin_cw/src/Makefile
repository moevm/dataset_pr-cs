all: main.o ChangeSym.o Input.o Outputs.o RemoveSentences.o SortByLatin.o UniqueWordsCount.o
	gcc ChangeSym.o Input.o main.o Outputs.o RemoveSentences.o SortByLatin.o UniqueWordsCount.o -o cw
main.o: main.c ChangeSym.h RemoveSentences.h SortByLatin.h UniqueWordsCount.h Structs.h Input.h Outputs.h
	gcc -c main.c
ChangeSym.o: ChangeSym.c ChangeSym.h Structs.h
	gcc -c ChangeSym.c
Input.o: Input.c Input.h Structs.h
	gcc -c Input.c
Outputs.o: Outputs.c Outputs.h Structs.h
	gcc -c Outputs.c
RemoveSentences.o: RemoveSentences.c RemoveSentences.h Structs.h
	gcc -c RemoveSentences.c
SortByLatin.o: SortByLatin.c SortByLatin.h Structs.h
	gcc -c SortByLatin.c
UniqueWordsCount.o: UniqueWordsCount.c UniqueWordsCount.h Structs.h
	gcc -c UniqueWordsCount.c
clean:
	rm *.o
