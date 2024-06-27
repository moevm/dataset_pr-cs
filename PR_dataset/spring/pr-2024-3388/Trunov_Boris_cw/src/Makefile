all: main.o read_bmp.o save_bmp.o reverse_color.o gray_image.o draw_filled_circle.o print_info_header.o help.o check_coords.o resize.o draw_line.o set_pixel.o failure.o ramka.o check_line_metainfo.o processing.o
	gcc main.o read_bmp.o save_bmp.o reverse_color.o gray_image.o draw_filled_circle.o print_info_header.o help.o check_coords.o resize.o draw_line.o set_pixel.o failure.o check_line_metainfo.o ramka.o processing.o -lm -o cw

maio.o: main.c processing.h
	gcc -c main.c

processing.o: main.c bmp.h save_bmp.h read_bmp.h reverse_color.h gray_image.h print_info_header.h help.h check_coords.h failure.h draw_line.h resize.h check_line_metainfo.h defines.h ramka.h processing.h
	gcc -c processing.c

save_bmp.o: save_bmp.c save_bmp.h bmp.h
	gcc -c save_bmp.c

read_bmp.o: read_bmp.c read_bmp.h bmp.h failure.h
	gcc -c read_bmp.c

reverse_color.o: reverse_color.c reverse_color.h bmp.h set_pixel.h
	gcc -c reverse_color.c

gray_image.o: gray_image.c gray_image.h bmp.h set_pixel.h
	gcc -c gray_image.c

print_info_header.o: print_info_header.c print_info_header.h bmp.h
	gcc -c print_info_header.c

check_coords.o: check_coords.c check_coords.h bmp.h
	gcc -c check_coords.c

help.o: help.c help.h bmp.h
	gcc -c help.c

failure.o: failure.c failure.h
	gcc -c failure.c

draw_line.o: draw_line.c draw_line.h bmp.h set_pixel.h draw_filled_circle.h
	gcc -c draw_line.c

check_line_metainfo.o: check_line_metainfo.c check_line_metainfo.h bmp.h failure.h
	gcc -c check_line_metainfo.c

set_pixel.o: set_pixel.c set_pixel.h bmp.h
	gcc -c set_pixel.c

draw_filled_circle.o: draw_filled_circle.c draw_filled_circle.h bmp.h set_pixel.h
	gcc -c draw_filled_circle.c

resize.o: resize.c resize.h bmp.h failure.h
	gcc -c resize.c

ramka.o: ramka.c ramka.h bmp.h failure.h
	gcc -c ramka.c

clear:
	rm *.o
	rm cw
