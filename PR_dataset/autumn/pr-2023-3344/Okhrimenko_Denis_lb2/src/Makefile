CC = gcc
CFLAG =-std=gnu99 -Wall
NAME_OF_EXE = menu
SRC = menu.c abs_max.c abs_min.c diff.c sum.c

all: $(NAME_OF_EXE)

$(NAME_OF_EXE): $(SRC:.c=.o)
	$(CC) $(CFLAG) $(SRC:.c=.o) -o $(NAME_OF_EXE)

menu.o:
	$(CC) $(CFLAG) -c menu.c

abs_min.o:
	$(CC) $(CFLAG) -c abs_min.c

abs_max.o:
	$(CC) $(CFLAG) -c abs_max.c

diff.o:
	$(CC) $(CFLAG) -c diff.c

sum.o:
	$(CC) $(CFLAG) -c sum.c

clean: 
	rm *.o
