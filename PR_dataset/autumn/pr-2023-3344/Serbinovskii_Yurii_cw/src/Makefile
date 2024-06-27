all: main.o change_text.o cmps.o avg_len.o input.o last.o
	gcc -std=c99 -g -o cw *.o
main.o: main.c change_text.h cmps.h structures.h
	gcc -c -g -std=c99 main.c
change_text.o: change_text.c cmps.h structures.h
	gcc -c -g -std=c99 change_text.c
cmps.o: cmps.c structures.h avg_len.h
	gcc -c -g -std=c99 cmps.c
avg_len.o: avg_len.c
	gcc -c -g -std=c99 avg_len.c
input.o: avg_len.c structures.h change_text.h
	gcc -c -g -std=c99 input.c
last.o:
	gcc -c -g -std=c99 last.c

clean:
	rm -rf *.o all