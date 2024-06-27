TARGET = cw
CC = gcc

PREF_CORE = ./core/
PREF_HEADER = ./header/
PREF_BIN = ./bin/

CFLAGS = -Wall -std=gnu99 -I$(PREF_HEADER)

CORE  = $(wildcard $(PREF_CORE)*.c)
OBJ = $(patsubst $(PREF_CORE)%.c, $(PREF_BIN)%.o, $(CORE))

all : make_bin $(TARGET)

$(TARGET) : $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(PREF_BIN)%.o : $(PREF_CORE)%.c
	$(CC) $(CFLAGS) -c $< -o $@

make_bin :
	mkdir -p $(PREF_BIN)

clean :
	rm $(TARGET)
	rm -rf $(PREF_BIN)
