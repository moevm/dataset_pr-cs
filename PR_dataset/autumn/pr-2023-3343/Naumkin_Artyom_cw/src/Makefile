CC = gcc
RM = rm -rf
EXE = cw

OBJDIR = object
INCDIR = include
SRCDIR = sources

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))

all: $(EXE)

$(EXE): $(OBJECTS)
	$(CC) -I$(INCDIR) $(OBJECTS) -o $(EXE)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) -I$(INCDIR) -c $< -o $@


clean:
	$(RM) $(OBJDIR) $(EXE)
