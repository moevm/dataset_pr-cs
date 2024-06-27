cw: main.o TextRead.o DelRepStr.o PaintWords.o RemoveNumText.o SortLenLast.o PrintUpper.o PrintText.o  CountSum.o
	gcc -o cw main.o TextRead.o DelRepStr.o PaintWords.o RemoveNumText.o SortLenLast.o PrintUpper.o PrintText.o CountSum.o -lm

main.o: main.c TextRead.h DelRepStr.h PaintWords.h RemoveNumText.h SortLenLast.h PrintUpper.h PrintText.h CountSum.h
	gcc -c main.c

TextRead.o: TextRead.c TextRead.h Structs.h
	gcc -c TextRead.c

DelRepStr.o: DelRepStr.c DelRepStr.h Structs.h
	gcc -c DelRepStr.c

PaintWords.o: PaintWords.c PaintWords.h Structs.h
	gcc -c PaintWords.c

RemoveNumText.o: RemoveNumText.c RemoveNumText.h Structs.h
	gcc -c RemoveNumText.c

SortLenLast.o: SortLenLast.c SortLenLast.h Structs.h
	gcc -c SortLenLast.c

PrintUpper.o: PrintUpper.c PrintUpper.h Structs.h
	gcc -c PrintUpper.c

PrintText.o: PrintText.c PrintText.h Structs.h
	gcc -c PrintText.c

CountSum.o: CountSum.c CountSum.h Structs.h
	gcc -c CountSum.c

clean:
	rm -f cw *.o
