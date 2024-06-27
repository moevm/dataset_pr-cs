CC = gcc
FLAGS = -g -std=c99

cw: main.o textio.o errors.o shift.o chars.o words.o uppercase.o function8.o
	$(CC) main.o textio.o errors.o shift.o chars.o words.o uppercase.o function8.o -o cw

main.o:
	$(CC) -c main.c $(FLAGS)

textio.o:
	$(CC) -c textio.c $(FLAGS)

errors.o:
	$(CC) -c errors.c $(FLAGS)

shift.o:
	$(CC) -c shift.c $(FLAGS)

chars.o:
	$(CC) -c chars.c $(FLAGS)

words.o:
	$(CC) -c words.c $(FLAGS)

uppercase.o:
	$(CC) -c uppercase.c $(FLAGS)

function8.o:
	$(CC) -c function8.c $(FLAGS)

clean:
	rm main.o textio.o errors.o shift.o chars.o words.o uppercase.o cw