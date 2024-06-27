//
// Created by zoomie on 5/22/24.
//

#include "rhombus.h"
#include <png.h>
#include "image_data.h"
#include "utils.h"
#include <math.h>
#include "string.h"

//png_bytepp draw_triangle(image_data image, pixel color, long x, long y) {
//    double hypho = sqrt(pow(y, 2) + pow(x, 2));
//    double angle = asin((double)y / hypho);
//    angle = (double)(round(angle * 100)/100);
//
//    double angle1 = 0;
//
//    for(int i = y; i >= 0; i--) {
//        for(int j = 0; j <= x; j++) {
//
//            double k = x - j;
//            double k2 = i;
//            double h = sqrt(pow(k, 2) + pow(k2, 2));
//
//            if(h!=0) {
//                angle1 = asin(k2 / h);
//                angle1 = (double)(round(angle1 * 100)/100);
//            } else {
//                color_row(&image.rows[i][j], color, x - j, image.width);
//            }
//
//            if (angle1 >= angle) {
//                color_row(&image.rows[i][j], color, x - j, image.width);
//                angle1 = 0;
//                break;
//            }
//        }
//    }
//
//    return (png_bytepp)image.rows;
//}
//
//png_bytepp rhombus(image_data image, pixel color) {
//    long first_coord_y = image.height / 2, first_coord_x = 0,
//
//        second_coord_y = 0, second_coord_x = image.width / 2,
//
//        third_coord_y = first_coord_y, third_coord_x = image.width - 1,
//
//        forth_coord_y = image.height - 1, forth_coord_x = image.width - 1;
//
//    draw_triangle(image, color, second_coord_x, first_coord_y);
//    struct array_Array_pixel arr = get_columns_raw(image, image.width, image.height, 0, 0, NULL, 1);
//
//    for(int i = 0; i < image.height; i++) {
//        memcpy(image.rows[i], arr.arr[i].arr, );
//    }
//
//    draw_triangle(image, color, second_coord_x, first_coord_y);
//}
//
// Created by zoomie on 5/22/24.
//

#include "rhombus.h"
#include <math.h>

double calc_y(double k, long x, double b) {
    return k * x - b;
}

_Bool check_left_up(long y, long x, double k, double b) {
    return y >= round(calc_y(k, x, b));
}

_Bool check_right_up(long y, long x, double k, double b) {
    return y >= round(calc_y(k, x, b));
}

_Bool check_left_down(long y, long x, double k, double b) {
    return y <= round(calc_y(k, x, b));

}

_Bool check_right_down(long y, long x, double k, double b) {
    return y <= round(calc_y(k, x, b));
}


png_bytepp rhombus(image_data image, pixel RGB) {
    double k = (double)image.height / image.width;
    double b = (double)image.height / 2;

    for (long i = 0; i < image.height; ++i)
        for (long j = 0; j < image.width; ++j)
            if (check_left_up(i, j, k, b)
                && check_right_up(i, j, -k, -b)
                && check_left_down(i, j, -k, -b * 3)
                && check_right_down(i, j, k, -b))
                image.rows[i][j] = RGB;

    return (png_bytepp)image.rows;
}