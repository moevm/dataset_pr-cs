SOURCES = menu.c Func_index_last_odd.c Func_index_first_even.c sum_before_even_and_after_odd.c sum_between_even_odd.c
OBJECTS = $(SOURCES:.c=.o)

all:menu
menu:$(OBJECTS)
	gcc -std=gnu99 $^ -o menu

%.o : %.c
	gcc -std=gnu99 -c -o $@ $<

clean:
	rm -rf *.o menu