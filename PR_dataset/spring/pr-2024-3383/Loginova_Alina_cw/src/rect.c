#include "rect.h"
#include "utils.h"
#include "ornament.h"
#include <math.h>

pixel** draw_rect(long left_up_x, long left_up_y, long right_down_x, long right_down_y,
                     pixel RGB, image_data image) {
    for (long i = left_up_y; i <= min(right_down_y, image.height - 1); i++) {
        if(i >= 0 && i < image.height)
            color_row(&image.rows[i][clamp_positive(left_up_x)], RGB, min(right_down_x, image.width - 1) - clamp_positive(left_up_x), image.width);
    }
    return image.rows;
}

png_bytepp rect(long left_up_x, long left_up_y, long right_down_x, long right_down_y, long int_thickness, pixel RGB,
                      char* fill, pixel RGB_f, image_data image, _Bool ornament) {

    long left_up_x_left, left_up_y_left, right_down_x_left, right_down_y_left,
        left_up_x_right, left_up_y_right, right_down_x_right, right_down_y_right,
        left_up_x_bottom, left_up_y_bottom, right_down_x_bottom, right_down_y_bottom,
        left_up_x_top, left_up_y_top, right_down_x_top, right_down_y_top;

    if(fill) {
        image.rows = draw_rect(left_up_x, left_up_y, right_down_x, right_down_y, RGB_f, image);
    }

    if(!ornament) {
        image.rows = print_circle(left_up_x, left_up_y, ceilf((float) int_thickness / 4) + 1, int_thickness / 2, RGB, image);
        image.rows = print_circle(left_up_x, right_down_y, ceilf((float)int_thickness / 4) + 1, int_thickness / 2, RGB, image);
        image.rows = print_circle(right_down_x, right_down_y, ceilf((float)int_thickness / 4) + 1, int_thickness / 2, RGB, image);
        image.rows = print_circle(right_down_x, left_up_y, ceilf((float)int_thickness / 4) + 1, int_thickness / 2, RGB, image);

        left_up_x_left = left_up_x - int_thickness / 2;
        left_up_y_left = left_up_y;
        right_down_x_left = left_up_x + int_thickness / 2;
        right_down_y_left = right_down_y;

        left_up_x_right = right_down_x - int_thickness / 2;
        left_up_y_right = left_up_y;
        right_down_x_right = right_down_x + int_thickness / 2;
        right_down_y_right = right_down_y;

        left_up_x_bottom = left_up_x;
        left_up_y_bottom = right_down_y - int_thickness / 2;
        right_down_x_bottom = right_down_x;
        right_down_y_bottom = right_down_y + int_thickness / 2;

        left_up_x_top = left_up_x;
        left_up_y_top = left_up_y - int_thickness / 2;
        right_down_x_top = right_down_x;
        right_down_y_top = left_up_y + int_thickness / 2;
    } else {
        left_up_x_left = left_up_x;
        left_up_y_left = left_up_y;
        right_down_x_left = left_up_x + int_thickness;
        right_down_y_left = right_down_y;

        left_up_x_right = right_down_x - int_thickness;
        left_up_y_right = left_up_y;
        right_down_x_right = right_down_x;
        right_down_y_right = right_down_y;

        left_up_x_bottom = left_up_x;
        left_up_y_bottom = right_down_y - int_thickness;
        right_down_x_bottom = right_down_x;
        right_down_y_bottom = right_down_y;

        left_up_x_top = left_up_x;
        left_up_y_top = left_up_y;
        right_down_x_top = right_down_x;
        right_down_y_top = left_up_y + int_thickness;
    }
    image.rows = draw_rect(left_up_x_left, left_up_y_left, right_down_x_left, right_down_y_left, RGB, image);
    image.rows = draw_rect(left_up_x_right, left_up_y_right, right_down_x_right, right_down_y_right, RGB, image);
    image.rows = draw_rect(left_up_x_bottom, left_up_y_bottom, right_down_x_bottom, right_down_y_bottom, RGB, image);
    image.rows = draw_rect(left_up_x_top, left_up_y_top, right_down_x_top, right_down_y_top, RGB, image);

    return (png_bytepp)image.rows;
}