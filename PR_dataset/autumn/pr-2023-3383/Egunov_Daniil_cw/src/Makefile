all: cw

cw: main.o token.o sentence.o text.o input.o output.o text_processing.o utils.o
	gcc main.o token.o sentence.o text.o input.o output.o text_processing.o utils.o -o cw
	rm -rf *.o *.h.gch

main.o: main.c input.h output.h text_processing.h
	gcc -c main.c

token.o: token.c token.h
	gcc -c token.c

sentence.o: sentence.c sentence.h token.h
	gcc -c sentence.c

text.o: text.c text.h sentence.h token.h
	gcc -c text.c

input.o: input.c input.h text.h sentence.h token.h
	gcc -c input.c

output.o: output.c output.h text.h sentence.h token.h
	gcc -c output.c

text_processing.o: text_processing.c text_processing.h text.h sentence.h token.h utils.h
	gcc -c text_processing.c

utils.o: utils.c utils.h
	gcc -c utils.c

clean:
	rm -rf *.o *.h.gch cw
