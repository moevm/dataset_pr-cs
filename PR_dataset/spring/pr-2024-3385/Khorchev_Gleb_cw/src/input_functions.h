#include "bmp_structs.h"

Rgb **read_bmp(char file_name[], BitmapFileHeader* bmfh, BitmapInfoHeader* bmif);

void write_bmp(char file_name[], Rgb **arr, BitmapFileHeader* bmfh, BitmapInfoHeader* bmif);