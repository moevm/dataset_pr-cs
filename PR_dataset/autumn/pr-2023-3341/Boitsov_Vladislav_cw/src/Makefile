TARGET = cw
CC = gcc

SOURCE = ./src/
HEADER = ./headers/
BIN = ./bin/

CFLAGS = -Wall -std=gnu99 -I$(HEADER)

SRC = $(wildcard $(SOURCE)*.c)
OBJ = $(patsubst $(SOURCE)%.c, $(BIN)%.o, $(SRC))

all : create_bin_folder $(TARGET)

$(TARGET) : $(OBJ)
	@$(CC) $(CFLAGS) $^ -o $@

$(BIN)%.o : $(SOURCE)%.c 
	@$(CC) $(CFLAGS) -c $< -o $@

create_bin_folder :
	@mkdir -p $(BIN)

clean:
	@rm $(TARGET)
	@rm -rf $(BIN)