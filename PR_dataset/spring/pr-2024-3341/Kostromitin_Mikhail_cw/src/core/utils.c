#include "utils.h"


int
check_if_bmp(BitmapFileHeader* bmfh){
    if (bmfh->signature != 19778 || bmfh->reserved1 != 0 || bmfh->reserved2 != 0){
        return 0;
    }
    return 1;
}


int
color_cmp(Rgb f, Rgb s){
    if (f.g == s.g && f.r == s.r && f.b == s.b){
        return 1;
    }
    return 0;
}


void
color_change(Rgb* dest, Rgb src){
    (*dest).b = src.b;
    (*dest).g = src.g;
    (*dest).r = src.r;
}


int
color_validator(Rgb color){
    if (color.r < 0 || color.r > 255 || color.g < 0 || color.g > 255 || color.b < 0 || color.b > 255){
        return 0;
    }
    return 1;
}


int
coord_validator(int max, int coord0, int coord1){
    if (coord0 < 0 || coord0 > max || coord1 < 0 || coord1 > max){
        return 0;
    }
    return 1;
}


unsigned int
padding(unsigned int w){
    unsigned int padding = (w * sizeof(Rgb)) % 4;
    if (padding) padding = 4 - padding;
    return padding;
}


unsigned int
row_len(unsigned int w){
    return (w * sizeof(Rgb) + padding(w));
}


int
component_validator(int component){
    if (component > 255 || component < 0){
        return 1;
    }
    return 0;
}


Rgb
parse_color(char color_string[]){
    Rgb color;
    char* tmp;
    int curr_color;

    tmp = strtok(color_string, ".");
    curr_color = atoi(tmp);
    if (component_validator(curr_color)){
        printf("Error 45: Invalid component for color replacement");
        exit(45);
    }
    color.r = curr_color;

    tmp = strtok(NULL, ".");
    curr_color = atoi(tmp);
    if (component_validator(curr_color)){
        printf("Error 45: Invalid component for color replacement");
        exit(45);
    }
    color.g = curr_color;

    tmp = strtok(NULL, ".");
    curr_color = atoi(tmp);
    if (component_validator(curr_color)){
        printf("Error 45: Invalid component for color replacement");
        exit(45);
    }
    color.b = curr_color;

    return color;
}


void
help(){
    printf("Программа для обработки файла формата bmp.\n");
    printf("\t-p / --input - имя входного файла.\n");
    printf("\t-i / --info - флаг для печати подробной информации о bmp-файле.\n");
    printf("\t-o / --output - переопределение названия конечного bmp-файла.\n");
    printf("Заменяет все пиксели одного заданного цвета на другой цвет. Флаг для выполнения данной операции: `--color_replace`. Функционал определяется:\n");
    printf("\t--old_color - цвет, который необходимо заменить: строчка вида \"rrr.ggg.bbb\", где rrr/ggg/bbb – числа, задающие цветовую компоненту.\n");
    printf("\t--new_color - новый цвет: строчка вида \"rrr.ggg.bbb\", где rrr/ggg/bbb – числа, задающие цветовую компоненту.\n");
    printf("Фильтр rgb-компонент. Флаг для выполнения данной операции: `--rgbfilter`. Этот инструмент должен позволять для всего изображения либо установить в диапазоне от 0 до 255 значение заданной компоненты. Функционал определяется:\n");
    printf("\t--component_name - имя компоненты, которую нужно заменить. Возможные значения `red`, `green` и `blue`\n");
    printf("\t--component_value - значение, на которое требуется заменить значения компоненты. Принимает значение в виде числа от 0 до 255.\n");
    printf("Разделяет изображение на N*M частей. Флаг для выполнения данной операции: `--split`. Реализация: провести линии заданной толщины. Функционал определяется:\n");
    printf("\t--number_x - количество частей по “оси” Y. На вход принимает число больше 1.\n");
    printf("\t--number_y - количество частей по “оси” X. На вход принимает число больше 1.\n");
    printf("\t--thickness - толщина линии. На вход принимает число больше 0.\n");
    printf("\t--color - цвет линии, цвет задаётся строкой \"rrr.ggg.bbb\", где rrr/ggg/bbb – числа, задающие цветовую компоненту.\n");
    printf("При последовательном вводе операция, они имеют следующий приоритет выполнения: color_replace, rgbfilter, split.\n");
}


void
info(BitmapInfoHeader info_header, BitmapFileHeader file_header){
    print_file_header(file_header);
    print_info_header(info_header);
}


void
print_file_header(BitmapFileHeader header){
    printf("signature:\t%x (%hu)\n", header.signature, header.signature);
    printf("filesize:\t%x (%u)\n", header.filesize, header.filesize);
    printf("reserved1:\t%x (%hu)\n", header.reserved1, header.reserved1);
    printf("reserved2:\t%x (%hu)\n", header.reserved2, header.reserved2);
    printf("pixelArrOffset:\t%x (%u)\n", header.pixelArrOffset, header.pixelArrOffset);
}


void
print_info_header(BitmapInfoHeader header){
    printf("headerSize:\t%x (%u)\n", header.headerSize, header.headerSize);
    printf("width: \t%x (%u)\n", header.width, header.width);
    printf("height: \t%x (%u)\n", header.height, header.height);
    printf("planes: \t%x (%hu)\n", header.planes, header.planes);
    printf("bitsPerPixel:\t%x (%hu)\n", header.bitsPerPixel, header.bitsPerPixel);
    printf("compression:\t%x (%u)\n", header.compression, header.compression);
    printf("imageSize:\t%x (%u)\n", header.imageSize, header.imageSize);
    printf("xPixelsPerMeter:\t%x (%u)\n", header.xPixelsPerMeter, header.xPixelsPerMeter);
    printf("yPixelsPerMeter:\t%x (%u)\n", header.yPixelsPerMeter, header.yPixelsPerMeter);
    printf("colorsInColorTable:\t%x (%u)\n", header.colorsInColorTable, header.colorsInColorTable);
    printf("importantColorCount:\t%x (%u)\n", header.importantColorCount, header.importantColorCount);
}
