CC = gcc 
PROGRAM = cw
CFLAGS = -Wl,-rpath=./ -L. -lCw -lpng -lm
LIBNAME = libCw.so
HNAME = cw.h

all: $(PROGRAM)

$(PROGRAM): main.c $(LIBNAME) 
	$(CC) main.c $(CFLAGS) -o $(PROGRAM)

$(LIBNAME): cw.c $(HNAME) 
	$(CC) -o $(LIBNAME) -shared -fPIC cw.c	

install: install_so install_h

install_so: $(LIBNAME)
	install -m 777 $(LIBNAME) /usr/local/lib

install_h:
	install -m 777 $(HNAME) /usr/local/include

clean:
	rm $(LIBNAME) $(PROGRAM)