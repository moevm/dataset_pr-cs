FLAG = -std=gnu99
SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))

all: $(OBJ)
	gcc $(FLAG) $(OBJ) -o menu

%.o: %.c
	gcc -c $(FLAG) $< -o $@

clean:
	rm -f *.o
