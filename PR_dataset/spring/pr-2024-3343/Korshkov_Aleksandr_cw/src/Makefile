CC = gcc
CFLAGS = -g -Werror -std=gnu99
LIBS = -lpng -lm
SRCDIR = sources
OBJDIR = objects
INCDIR = include

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))

EXECUTABLE = cw

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean_objects:
	rm -rf $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(EXECUTABLE)

.PHONY: all, clean, clean_objects