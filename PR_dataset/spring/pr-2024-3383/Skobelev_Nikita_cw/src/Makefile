MAKEFLAGS += -j4
CC = g++
CFLAGS = -std=c++14
FILES = main.cpp BMP.cpp read_bmp.cpp write_bmp.cpp error_type.cpp split.cpp filled_rect.cpp circle.cpp rgbfilter.cpp help.cpp info.cpp
OBJ = main.o BMP.o read_bmp.o write_bmp.o error_type.o split.o filled_rect.o circle.o rgbfilter.o help.o info.o

all: main

main: main.o  source/BMP.o  source/read_bmp.o  source/write_bmp.o  source/error_type.o  source/split.o  source/filled_rect.o  source/rgbfilter.o  source/circle.o  source/help.o  source/info.o source/defence.o
	g++ main.o  source/BMP.o  source/read_bmp.o  source/write_bmp.o  source/error_type.o  source/split.o  source/filled_rect.o  source/rgbfilter.o  source/circle.o  source/help.o  source/info.o source/defence.o -o cw
main.o: main.cpp write_bmp.o header/class_bmp.h header/struct_bmp.h
	g++ -c main.cpp -o ./main.o
BMP.o:  source/BMP.cpp header/class_bmp.h header/struct_bmp.h
	g++ -c source/BMP.cpp -o source/BMP.o
read_bmp.o:  source/read_bmp.cpp header/class_bmp.h header/struct_bmp.h
	g++ -c source/read_bmp.cpp -o source/read_bmp.o
write_bmp.o:  source/write_bmp.cpp header/class_bmp.h header/struct_bmp.h
	g++ -c source/write_bmp.cpp -o source/write_bmp.o
error_type.o:  source/error_type.cpp header/class_bmp.h header/struct_bmp.h
	g++ -c source/error_type.cpp -o source/error_type.omake
split.o:  source/split.cpp header/class_bmp.h header/struct_bmp.h
	g++ -c source/split.cpp -o source/split.o
filled_rect.o:  source/filled_rect.cpp header/class_bmp.h header/struct_bmp.h
	g++ -c source/filled_rect.cpp -o source/filled_rect
rgbfilter.o:  source/rgbfilter.cpp header/class_bmp.h header/struct_bmp.h
	g++ -c source/rgbfilter.cpp -o source/rgbfilter.o
circle.o:  source/circle.cpp header/class_bmp.h header/struct_bmp.h
	g++ -c source/circle.cpp -o source/circle
help.o:  source/help.cpp header/class_bmp.h header/struct_bmp.h
	g++ -c source/help.cpp -o source/help.o
info.o:  source/info.cpp header/class_bmp.h header/struct_bmp.h
	g++ -c source/info.cpp -o source/info.o
defence.o: source/defence.cpp header/class_bmp.h header/struct_bmp.h
	g++ -c source/defence.cpp  -o source/defence.o
main_full: $(FILES)
	$(CC) $(CFLAGS) -o cw $(FILES)

clean:
	rm -rf *.o && rm -rf source/*.o && rm -rf cw
