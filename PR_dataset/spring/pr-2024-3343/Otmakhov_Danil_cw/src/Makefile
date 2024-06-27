EXECUTABLE = cw

CC = gcc
CFLAGS = -I$(INCLUDE_DIR)

SOURCES_DIR = sources
INCLUDE_DIR = include
OBJECTS_DIR = objects

SOURCES = $(wildcard $(SOURCES_DIR)/*.c)
OBJECTS = $(patsubst $(SOURCES_DIR)/%.c, $(OBJECTS_DIR)/%.o, $(SOURCES))


all : $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE)

$(OBJECTS_DIR)/%.o : $(SOURCES_DIR)/%.c
	@mkdir -p $(OBJECTS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -rf -r $(OBJECTS_DIR) $(EXECUTABLE)
