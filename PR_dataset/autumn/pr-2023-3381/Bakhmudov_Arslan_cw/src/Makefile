# Compiler
CC = gcc
# Compiling flags
CFLAGS = 
# Linking flags
LFLAGS = 
# Program name
OUT = cw

OBJ_FILES = main.o struct.o temp.o config.o functions.o safety.o



all: compile clean

compile: $(OBJ_FILES)
	$(CC) $(LFLAGS) $(OBJ_FILES) -o $(OUT)

main.o: main.c temp.h safety.h macros.h config.h struct.h functions.h
	$(CC) $(CFLAGS) -c main.c -o main.o

struct.o: struct.c safety.h macros.h struct.h
	$(CC) $(CFLAGS) -c struct.c -o struct.o

temp.o: temp.c temp.h
	$(CC) $(CFLAGS) -c temp.c -o temp.o

config.o: config.c config.h macros.h
	$(CC) $(CFLAGS) -c config.c -o config.o

functions.o: functions.c safety.h macros.h struct.h functions.h
	$(CC) $(CFLAGS) -c functions.c -o functions.o

safety.o: safety.c safety.h
	$(CC) $(CFLAGS) -c safety.c -o safety.o

clean:
	rm -f *.o

execute:
	./$(OUT)

delete:
	rm $(OUT)