CC = gcc
CFLAGS = -Wall -std=gnu99
SRC = menu.c abs_max.c abs_min.c diff.c sum.c
OBJ = $(SRC:.c=.o)
OUT = menu

all: $(OUT)
	$(CC) $(CFLAGS) -o $@ $(OBJ)


$(OUT): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^
	
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OUT) $(OBJ)
