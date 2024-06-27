SRCS := $(wildcard *.c)
OBJS=$(SRCS:.c=.o)

all:	menu
menu:	$(OBJS)
	gcc -Wall $(OBJS) -o $@

%.o:	%.c
	gcc -Wall -c $< -o $@

clean:
	rm *.o
	rm menu
