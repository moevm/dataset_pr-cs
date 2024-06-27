CC=gcc

cw: makeobj obj/main.o obj/inputText.o obj/getChoise.o obj/makeDate.o obj/reverseWithPunctuation.o obj/sort.o obj/delete.o obj/helpAboutFunctions.o
	$(CC) obj/main.o obj/inputText.o obj/getChoise.o obj/makeDate.o obj/reverseWithPunctuation.o obj/sort.o obj/delete.o obj/helpAboutFunctions.o -o cw

makeobj:
	mkdir obj

obj/inputText.o: inputText.c header_files/inputText.h header_files/structures.h
	$(CC) -c -o obj/inputText.o inputText.c

obj/sort.o: sort.c header_files/sort.h header_files/structures.h
	$(CC) -c -o obj/sort.o sort.c

obj/getChoise.o: getChoise.c header_files/getChoise.h
	$(CC) -c -o obj/getChoise.o getChoise.c

obj/delete.o: delete.c header_files/delete.h header_files/structures.h
	$(CC) -c -o obj/delete.o delete.c

obj/makeDate.o: makeDate.c header_files/makeDate.h header_files/structures.h
	$(CC) -c -o obj/makeDate.o makeDate.c

obj/helpAboutFunctions.o: helpAboutFunctions.c header_files/helpAboutFunctions.h
	$(CC) -c -o obj/helpAboutFunctions.o helpAboutFunctions.c

obj/reverseWithPunctuation.o: reverseWithPunctuation.c header_files/reverseWithPunctuation.h header_files/structures.h
	$(CC) -c -o obj/reverseWithPunctuation.o reverseWithPunctuation.c

obj/main.o: main.c 
	$(CC) -c -o obj/main.o main.c

clean:
	rm -f obj/*.o cw && rmdir obj
