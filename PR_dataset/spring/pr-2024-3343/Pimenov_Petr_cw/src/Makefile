CC := gcc
CFLAGS :=
BUILDDIR := build
INCLUDEDIR := include
SRCDIR := src
EXECUTABLENAME = cw

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SOURCES))

all: $(EXECUTABLENAME)

$(EXECUTABLENAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -lpng -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -I $(INCLUDEDIR) -c $< -o $@

clean:
	@rm -rf $(BUILDDIR) $(EXECUTABLENAME)

.PHONY: all clean