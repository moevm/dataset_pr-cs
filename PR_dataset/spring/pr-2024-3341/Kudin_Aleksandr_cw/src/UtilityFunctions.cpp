#include "UtilityFunctions.h"
#include <iostream>

void description(){
    std::cout << "Course work for option 4.12, created by Kudin Aleksandr." << std::endl;
}

void outputHelp() {
    std::cout << "Help: данная программа предназначена для обработки BMP изображения." << std::endl <<
                 "Использование:" << std::endl <<
                 "--output [filename] : задать имя выходного файла (по умолчанию out.bmp)" << std::endl <<
                 "--input [filename] : задать имя входного BMP файла" << std::endl <<
                 "--info : вывод информации о BMP файле" << std::endl <<
                 "--squared_lines : нарисовать квадрат с диагоналями" << std::endl <<
                 "--rgbfilter : применить RGB фильтр к изображению" << std::endl <<
                 "--rotate : повернуть изображение" << std::endl <<
                 "Примеры ключей:" << std::endl <<
                 "--left_up x,y : координаты левого верхнего угла" << std::endl <<
                 "--right_down x,y : координаты правого нижнего угла" << std::endl <<
                 "--side_size [size] : размер стороны квадрата" << std::endl <<
                 "--thickness [size] : толщина линий" << std::endl <<
                 "--color rrr,ggg,bbb : цвет в формате RGB" << std::endl <<
                 "--fill : указывает, что фигура должна быть заполнена" << std::endl <<
                 "--fill_color rrr,ggg,bbb : цвет заливки фигуры" << std::endl <<
                 "--angle [degrees] : угол поворота изображения" << std::endl;
}

void outputInfo(BitmapInfoHeader &infoHeader){
    printf("BMP file info:\n1) Разрешение файла %dx%d.\n", infoHeader.width, infoHeader.height);
    printf("2) Размер файла: %d байтов\n", infoHeader.imageSize);
    printf("3) Глубина изображения: %d\n", infoHeader.bitsPerPixel);
    printf("4) Количество цветовых плоскостей: %d\n", infoHeader.planes);
}
