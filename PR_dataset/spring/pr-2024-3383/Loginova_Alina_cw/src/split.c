#include "split.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "print_usage.h"
#include "arrays.h"
#include "utils.h"

Array_Array_pixel split_side(long x, pixel RGB, long thickness, Array_Array_pixel rows) {

    long pixels_to_color = (x - 1) * thickness;
    long pixels_not_to_color = clamp_positive(rows.size - pixels_to_color);
    long segment_size = round_num((double)pixels_not_to_color / (double)x);

    Array_Array_pixel rows_to_color_x = create_Array_pixel_array(NULL);
    for(long i = segment_size; i < rows.size; i += segment_size + thickness) {
        append_Array_pixel_array(&rows_to_color_x, &rows.arr[i], thickness > rows.size - i ? rows.size - i : thickness);
    }

    for (long i = 0; i < rows_to_color_x.size; i++) {
        for (long j = 0; j < rows.arr->size; j++) {
            rows_to_color_x.arr[i].arr[j] = RGB;
        }
    }

    clear_Array_pixel_array(&rows_to_color_x);
    return rows;
}

png_bytepp split(long x, long y, pixel RGB, long thickness, image_data image) {
    Array_Array_pixel rows = create_Array_pixel_array(pixel_columns_deleter);

    for(long i = 0; i < image.height; i++) {
        Array_pixel row = create_pixel_array(NULL);
        append_pixel_array(&row, image.rows[i], image.width);
        add_Array_pixel_element(&rows, row);
    }

    /* делим по горизонтали */
    rows = split_side(y, RGB, thickness, rows);
    Array_Array_pixel upd_rows = get_columns(rows, 0, 0, NULL, 1);

    /* делим по вертикали */
    upd_rows = split_side(x, RGB, thickness, upd_rows);
    Array_Array_pixel split_image = get_columns(upd_rows, 0, 0, NULL, 0);

    for(long i = 0; i < image.height; i++) {
        free(image.rows[i]);
        image.rows[i] = split_image.arr[i].arr;
    }

    clear_Array_pixel_array(&rows);
    clear_Array_pixel_array(&upd_rows);

    return (png_bytepp)image.rows;
}
