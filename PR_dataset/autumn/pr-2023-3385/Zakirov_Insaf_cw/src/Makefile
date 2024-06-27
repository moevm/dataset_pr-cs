all: main.o myinout.o mystruct.o myfunc.o mysupport.o
	gcc main.o myinout.o mystruct.o myfunc.o mysupport.o -o cw

main.o: main.c
	gcc -c -std=c99 main.c

myinout.o: myinout.c myinout.h
	gcc -c -std=c99 myinout.c

mystruct.o: mystruct.c mystruct.h
	gcc -c -std=c99 mystruct.c

myfunc.o: myfunc.c myfunc.h
	gcc -c -std=c99 myfunc.c

mysupport.o: mysupport.c mysupport.h
	gcc -c -std=c99 mysupport.c

clean:
	rm -rf *.o cw