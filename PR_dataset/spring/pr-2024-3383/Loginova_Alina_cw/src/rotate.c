#include "rotate.h"
#include "utils.h"
#include <png.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arrays.h"

const int rotation_step = 90,
        full_rotation = 360;

Array_Array_pixel cut_intersection(long x_left, long y_top, long x_right, long y_bottom, image_data image) {
    Array_Array_pixel rows = create_Array_pixel_array(pixel_columns_deleter);
    pixel **pixel_rows = (pixel **)image.rows;
    pixel black = { 0, 0, 0 };
    for (long i = clamp_positive(y_top); i < min(image.height, y_bottom + 1); ++i) {
        Array_pixel row = create_pixel_array(NULL);
        for (long j = clamp_positive(x_left); j < min(image.width, x_right + 1); ++j) {
            add_pixel_element(&row, pixel_rows[i][j]);
            //pixel_rows[i][j] = black;
        }
        add_Array_pixel_element(&rows, row);
    }
    return rows;
}

void write_intersection(Array_Array_pixel intersection, long x_shift, long y_shift, image_data image) {
    if (!intersection.size) return;
    size_t loc_height = intersection.size, loc_width = intersection.arr[0].size;
    pixel **pixelRows = (pixel **)image.rows;
    for (long i = clamp_positive(y_shift), ir = abs_negative(y_shift); i < image.height && ir < loc_height; ++i, ++ir)
        for (long j = clamp_positive(x_shift), jr = abs_negative(x_shift); j < image.width && jr < loc_width; ++j, ++jr)
            pixelRows[i][j] = intersection.arr[ir].arr[jr];
}

png_bytepp rotate(long left_up_x, long left_up_y, long right_down_x, long right_down_y, long angle, image_data image) {

    int rotation_steps = (int)(((angle % full_rotation) + full_rotation) % full_rotation) / rotation_step;
    if (!rotation_steps) {
        printf("[rotate()] некорректное значение аргумента angle\n");
        exit(40);
    }

    long rect_width = right_down_x - left_up_x + 1,
         rect_height = right_down_y - left_up_y + 1,
         x_axis = (rect_width - 1) / 2 + left_up_x,
         y_axis = (rect_height - 1) / 2 + left_up_y,
         y_shift, x_shift;

    switch (rotation_steps) {
        case 3:
            y_shift = y_axis - (x_axis - left_up_x) + abs_negative(left_up_x),
            x_shift = x_axis - (right_down_y - y_axis) + clamp_positive(right_down_y - (image.height - 1));
            break;
        case 2:
            y_shift = left_up_y,
            x_shift = left_up_x;
            break;
        case 1:
            y_shift = y_axis - (x_axis - left_up_x) + clamp_positive(right_down_x - (image.width - 1)),
            x_shift = x_axis - (right_down_y - y_axis) + abs_negative(left_up_y);
            break;
        default:
            printf("[rotate()] ошибочный id вращения координаты");
            exit(40);
    }

    Array_Array_pixel intersection = cut_intersection(left_up_x, left_up_y, right_down_x - 1, right_down_y - 1, image);

    for (int i = 0; i < rotation_steps; ++i) {
        Array_Array_pixel temp = get_columns(intersection, 0, 0, 0, 0);
        clear_Array_pixel_array(&intersection);
        intersection = temp;
    }

    write_intersection(intersection, x_shift, y_shift, image);

    clear_Array_pixel_array(&intersection);
    return (png_bytepp)image.rows;
}
