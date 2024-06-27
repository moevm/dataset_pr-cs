CC=gcc
CFLAGS=-std=c99 -Wall

all: menu

menu: menu.o sum.o diff.o abs_min.o abs_max.o
  $(CC) $(CFLAGS) menu.o sum.o diff.o abs_min.o abs_max.o -o menu

menu.o: menu.c
  $(CC) $(CFLAGS) -c menu.c

sum.o: abs_max.c sum.c
  $(CC) $(CFLAGS) -c sum.c

diff.o: abs_max.c abs_min.c diff.c
  $(CC) $(CFLAGS) -c diff.c

abs_min.o: abs_min.c
  $(CC) $(CFLAGS) -c abs_min.c

abs_max.o: abs_max.c
  $(CC) $(CFLAGS) -c abs_max.c
