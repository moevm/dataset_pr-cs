# g++ main.cpp args.cpp image.cpp -o args -lpng -g
CC = g++
CFLAGS = -Ofast -flto -pipe -lpng -std=gnu++1z
EXE = cw
SRC = $(wildcard *.cpp) $(wildcard **/*.cpp)

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $(SRC) -lpng -o $(EXE)

run: $(EXE)
	./$(EXE)

