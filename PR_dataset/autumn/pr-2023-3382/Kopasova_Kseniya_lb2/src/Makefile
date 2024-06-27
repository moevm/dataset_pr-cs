SOURCES=menu.c abs_max.c abs_min.c diff.c sum.c
OBJECTS=$(SOURCES:.c=.o)

all: menu

menu: $(OBJECTS)
	gcc -std=gnu99 $^ -o menu

%.o : %.c
	gcc -std=gnu99 -c -o $@ $<

clean:
	rm -rf *.o menu
