C = gcc
CFLAGS = -std=c99
NAME = menu

all: compile clean

compile: menu.o min.o max.o diff.o sum.o
	$(C) menu.o min.o max.o diff.o sum.o $(CFLAGS) -o  $(NAME)

%.o: @.c
	$(C) $(CFLAGS) -c  $<.c

clean:
	rm -r *.o

all-exec: all
	echo "" && ./$(NAME)

