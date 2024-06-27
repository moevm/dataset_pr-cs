#include "info_functions.h"
void print_help() {
    printf("Программа обработки изображений формата BMP\n\n");
    printf("Использование:\n");
    printf("  program_name [options] -i input_file -o output_file\n\n");
    printf("Опции:\n");
    printf("  -i, --input <file>          Указать имя входного BMP-файла.\n");
    printf("  -o, --output <file>         Указать имя выходного BMP-файла.\n");
    printf("  -s, --squared_lines         Рисование квадрата с диагоналями.\n");
    printf("                              Параметры для рисования квадрата:\n");
    printf("                                --left_up <x.y>        Координаты левого верхнего угла квадрата.\n");
    printf("                                --side_size <n>        Размер стороны квадрата.\n");
    printf("                                --thickness <t>        Толщина линий квадрата.\n");
    printf("                                --color <rrr.ggg.bbb>  Цвет линий квадрата в формате RGB.\n");
    printf("                                --fill                 Флаг заполнения квадрата цветом.\n");
    printf("                                --fill_color <rrr.ggg.bbb> Цвет заполнения квадрата в формате RGB.\n");
    printf("                              Пример: --squared_lines --left_up 10.20 --side_size 100 --thickness 5 --color 255.0.0 --fill --fill_color 0.255.0\n");
    printf("\n");
    printf("  -f, --rgbfilter             Фильтр RGB-компонент.\n");
    printf("                              Параметры для фильтра RGB:\n");
    printf("                                --component_name <r/g/b>  Имя компонента (красный, зеленый или синий).\n");
    printf("                                --component_value <n>     Значение компонента (0-255).\n");
    printf("                              Пример: --rgbfilter --component_name r --component_value 128\n");
    printf("\n");
    printf("  -r, --rotate                Поворот изображения.\n");
    printf("                              Параметры для поворота:\n");
    printf("                                --left_up <x.y>        Координаты левого верхнего угла области поворота.\n");
    printf("                                --right_down <x.y>     Координаты правого нижнего угла области поворота.\n");
    printf("                                --angle <90/180/270>   Угол поворота (90, 180, 270 градусов).\n");
    printf("                              Пример: --rotate --left_up 10.20 --right_down 110.120 --angle 90\n");
    printf("\n");
    printf("  --info                      Вывод информации о BMP-файле (заголовок файла и заголовок информации).\n");
    printf("\n");
    printf("Примеры использования:\n");
    printf("  program_name -i input.bmp -o output.bmp --info\n");
    printf("  program_name -i input.bmp -o output.bmp --squared_lines --left_up 10.20 --side_size 100 --thickness 5 --color 255.0.0 --fill --fill_color 0.255.0\n");
    printf("  program_name -i input.bmp -o output.bmp --rgbfilter --component_name r --component_value 128\n");
    printf("  program_name -i input.bmp -o output.bmp --rotate --left_up 10.20 --right_down 110.120 --angle 90\n");
    printf("\n");
    printf("Замечания:\n");
    printf("  - Все координаты задаются в формате x.y, где x и y - целые числа.\n");
    printf("  - Цвета задаются в формате rrr.ggg.bbb, где r, g, и b - значения от 0 до 255.\n");
    printf("  - Убедитесь, что входные изображения являются файлами формата BMP, без сжатия с 24 битами на цвет\n");
    printf("  - При одновременном указании нескольких опций обработки (например, squared_lines и rotate), они будут выполняться последовательно в порядке их указания.\n");
}
void print_file_header(const BMP_FileHeader* header) {
    printf("Signature: %hu\n", header->signature);
    printf("Filesize: %u bytes\n", header->filesize);
    printf("Reserved1: %hu\n", header->reserved1);
    printf("Reserved2: %hu\n", header->reserved2);
    printf("Pixel Array Offset: %u bytes\n", header->pixelArrOffset);
}
void print_info_header(const BMP_InfoHeader* header) {
    printf("Header Size: %u bytes\n", header->headerSize);
    printf("Width: %u pixels\n", header->width);
    printf("Height: %u pixels\n", header->height);
    printf("Planes: %hu\n", header->planes);
    printf("Bits Per Pixel: %hu\n", header->bitsPerPixel);
    printf("Compression: %u\n", header->compression);
    printf("Image Size: %u bytes\n", header->imageSize);
    printf("X Pixels Per Meter: %u\n", header->xPixelsPerMeter);
    printf("Y Pixels Per Meter: %u\n", header->yPixelsPerMeter);
    printf("Colors in Color Table: %u\n", header->colorsInColorTable);
    printf("Important Color Count: %u\n", header->importantColorCount);
}
