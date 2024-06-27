TARGET = cw
CC = gcc

SOURCE = ./core/
HEADER = ./headers/
BIN = ./bin/

CFLAGS = -Wall -std=gnu99 -I$(HEADER)

SRC = $(wildcard $(SOURCE)*.c)
OBJ = $(patsubst $(SOURCE)%.c, $(BIN)%.o, $(SRC))

all : create_bin_folder $(TARGET)

$(TARGET) : $(OBJ)
	@$(CC) $(CFLAGS) $^ -o $@ -lm

$(BIN)%.o : $(SOURCE)%.c 
	@$(CC) $(CFLAGS) -c $< -o $@

create_bin_folder :
	@mkdir -p $(BIN)

clean:
	@rm -rf $(BIN) 
