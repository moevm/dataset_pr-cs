CC = gcc
RM = rm -rf
MEMORY_DEBUG_FLAGS = -fsanitize=address -fsanitize=undefined
COLOR_FLAG = -DLOG_USE_COLOR 
BASE_DEBUG_FLAGS = -pedantic -Wall -Wextra -Wformat -Wshadow -Wpointer-arith -Wcast-qual -Wstrict-prototypes -Wmissing-prototypes -Wstrict-overflow -Wundef -Wnested-externs -Wunreachable-code -Wlogical-op -Wvla -Wdisabled-optimization -Wcast-align -Wconversion -Wsign-compare -Wwrite-strings -Wimplicit-fallthrough -Wno-multichar
CFLAGS = -I$(INCDIR) 

SRCDIR = sources
INCDIR = include
OBJDIR = obj

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))
EXECUTABLE = cw

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJDIR) $(EXECUTABLE)
