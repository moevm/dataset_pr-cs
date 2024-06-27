comp = gcc
obj = main.o
exec = cw
flags = -lm -lpng
hdrs = signatures.h structs.h png_read_write.h main_funcs.h
cfile = main.c

build : $(obj)
	$(comp) $(obj) -o $(exec) $(flags)

main.o: $(cfile) $(hrds)
	$(comp) -c $(cfile) -o $(obj)

clean:
	rm *.o $(exec)