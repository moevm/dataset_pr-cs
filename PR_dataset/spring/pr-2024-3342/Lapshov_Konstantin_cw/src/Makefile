CC = gcc
CFLAGS = -c -Wall -std=c99

all: main.o bmpInteraction.o cliInterface.o functionsInteraction.o errors.o
	$(CC) main.o bmpInteraction.o cliInterface.o functionsInteraction.o errors.o -o cw -lm

main.o: main.c structures.h bmpInteraction.h cliInterface.h functionsInteraction.h
	$(CC) $(CFLAGS) main.c

bmpInteraction.o: bmpInteraction.c bmpInteraction.h structures.h errors.h
	$(CC) $(CFLAGS) bmpInteraction.c

cliInterface.o: cliInterface.c cliInterface.h structures.h errors.h
	$(CC) $(CFLAGS) cliInterface.c

functionsInteraction.o: functionsInteraction.c functionsInteraction.h structures.h errors.h bmpInteraction.h
	$(CC) $(CFLAGS) functionsInteraction.c

errors.o: errors.c errors.h
	$(CC) $(CFLAGS) errors.c

clean:
		rm *.o