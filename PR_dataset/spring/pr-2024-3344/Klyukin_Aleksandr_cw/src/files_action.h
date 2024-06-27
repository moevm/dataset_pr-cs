#ifndef COURSE_WORK_FILE_H
#define COURSE_WORK_FILE_H
#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

unsigned int padding(unsigned int w);
unsigned int row_len(unsigned int w);
int check_bmp_color_depth(FILE *file);
int check_bmp_signature(FILE *file);
Rgb **read_bmp(char file_name[], BitmapFileHeader *bmfh, BitmapInfoHeader *bmif);
void write_bmp(char file_name[], Rgb **arr, int H, int W, BitmapFileHeader bmfh, BitmapInfoHeader bmif);
void print_file_header(BitmapFileHeader header);
void print_info_header(BitmapInfoHeader header);

#endif //COURSE_WORK_DRAWING_LINE_FUNCTIONS_H