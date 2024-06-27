#include "print_func.h"

void printBMPHeaders(BMPfile* bmp_file)
{
  //printf("Описание BMP-файла \'%s\':\n", filename);
  printf("-----------------------------------------------------------------------------------------------------------------\n");
  printf("\tИдентификатор файла(file's signature): %c%c\n", bmp_file->bmpfh.ID[0], bmp_file->bmpfh.ID[1]);
  printf("\tРазмер файла в байтах(заголовки, данные): %u\n", bmp_file->bmpfh.file_size);
  printf("\tCмещение пиксельных данных в байтах(начальный адрес байта, в котором находится изображение): %d\n", bmp_file->bmpfh.offset_pixels);

  printf("\tРазмер заголовочной структуры в байтах: %d\n", bmp_file->bmpih.header_size);
  printf("\tШирина изображения в пикселях: %d\n", bmp_file->bmpih.width);
  printf("\tВысота изображения в пикселях: %d\n", bmp_file->bmpih.height);
  printf("\tДля каждого пикселя количество цветовых плоскостей: %d\n", bmp_file->bmpih.color_planes);
  printf("\tКоличество бит на пиксель: %d\n", bmp_file->bmpih.bits_per_pixel);
  printf("\tПризнак наличия сжатия: %d\n", bmp_file->bmpih.comp);
  printf("\tРазмер пиксельных данных в байтах: %d\n", bmp_file->bmpih.data_size);
  printf("\tКоличество пикселей на метр по высоте: %d\n", bmp_file->bmpih.pwidth);
  printf("\tКоличество пикселей на метр по ширине: %d\n", bmp_file->bmpih.pheight);
  printf("\tКоличество цветов в палитре: %d\n", bmp_file->bmpih.colors_count);
  printf("\tКоличество 'важных' цветов: %d\n", bmp_file->bmpih.imp_colors_count);
  printf("-----------------------------------------------------------------------------------------------------------------\n");
}

void printInfo()
{
  printf("--------------------------------------------------------------------------------------\n");
  printf("                      *Program's options*\n");
  printf("=    -i --info <file>          Input file name\n");
  printf("=    -o --output <file>        Output file name\n");
  printf("=    -I --info         Show file information\n");
  printf("=    -h --help         Show help about the program\n");
  printf("--------------------------------------------------------------------------------------\n");
  printf("=    --collage         Create a collage of size N*M from one image\n\n");
  printf("=         *-----*Flags for collage*-----*\n");
  printf("=    --number_y <value>          Number of images along the Y axis\n");
  printf("=    --number_x <value>          Number of images along the X axis\n");
  printf("--------------------------------------------------------------------------------------\n");
  printf("=    --mirror          Mirroring a specified area\n\n");
  printf("=          *-----*Flags for mirror*-----*\n");
  printf("=    --axis <value>                   Selecting the axis relative to which to reflect\n");
  printf("=    --left_up <value>.<value>        x, y left upper corner\n");
  printf("=    --right_down <value>.<value>     x, y lower right corner\n");
  printf("--------------------------------------------------------------------------------------\n");
  printf("=    --pentagram         Drawing a pentagram in a circle\n\n");
  printf("=          *-----*Flags for pentagram*-----*\n");
  printf("=    --center <value>.<value>                x, y center of the pentagram\n");
  printf("=    --radius <value>                        Radius of the pentagram\n");
  printf("=    --thickness <value>                     Line's thickness\n");
  printf("=    --color <value>.<value>.<value>         Line's color\n");
  printf("--------------------------------------------------------------------------------------\n");
  printf("=    --rect         Drawing a rectangle\n\n");
  printf("=          *-----*Flags for rectangle*-----*\n");
  printf("=    --left_up <value>.<value>                    x, y left upper corner\n");
  printf("=    --right_down <value>.<value>                 x, y lower right corner\n");
  printf("=    --thickness <value>                          Line's thickness\n");
  printf("=    --color <value>.<value>.<value>              Line's color\n");
  printf("=    --fill                                       Turning shape fill on or off\n");
  printf("=    --fill_color <value>.<value>.<value>         Shape's fill color\n");
  printf("--------------------------------------------------------------------------------------\n");
}

void printBMPPixels(BMPfile* bmp_file) 
{
  for(unsigned int y = 0; y < bmp_file->bmpih.height; y++) {
    for(unsigned int x = 0; x < bmp_file->bmpih.width; x++) {
      printf("%.3d %.3d %.3d\t ", bmp_file->data[y][x].red, bmp_file->data[y][x].green, bmp_file->data[y][x].blue);
    }
    printf("\n");
  }
}
