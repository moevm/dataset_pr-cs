all: main clean

main: main.o collectoprover.o bmp_class.o
	g++ main.o collectoprover.o bmp_class.o -o cw

main.o: main.cpp my_lib.h collectoprover.h bmp_class.h
	g++ -c -g main.cpp

bmp_class.o: bmp_class.cpp bmp_class.h my_lib.h collectoprover.h
	g++ -c -g bmp_class.cpp

collectoprover.o: collectoprover.cpp my_lib.h
	g++ -c -g collectoprover.cpp

clean:
	rm -rf *.o