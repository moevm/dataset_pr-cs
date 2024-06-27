CC = gcc
CFLAGS = -Wall -Wextra -std=c99

OBJS = max.o min.o diff.o sum.o menu.o

menu: $(OBJS)
	$(CC) $(CFLAGS) -o menu $(OBJS)

max.o: max.c
	$(CC) $(CFLAGS) -c max.c

min.o: min.c
	$(CC) $(CFLAGS) -c min.c

diff.o: diff.c
	$(CC) $(CFLAGS) -c diff.c

sum.o: sum.c
	$(CC) $(CFLAGS) -c sum.c

menu.o: menu.c
	$(CC) $(CFLAGS) -c menu.c

clean:
	rm -f $(OBJS) menu
