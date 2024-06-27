#include "utils.h"
#include <stdlib.h>

long min(long a, long b) {
    return a > b ? b : a;
}

long clamp_positive(long value) {
    return value < 0 ? 0 : value;
}

pixel parse_color(char *color) {
    char *endptr;

    long R = strtol(color, &endptr, 10);
    long G = strtol(endptr + 1, &endptr, 10);
    long B = strtol(endptr + 1, &endptr, 10);

    if(R < 0 || R > 255 || G < 0 || G > 255 || B < 0 || B > 255) {
        printf("[parse_color()] некорректные входные аргументы color\n");
        exit(40);
    }

    pixel p = { (char)R, (char)G, (char)B };
    return p;
}

long round_num(double num) {
    long cast = (long)num;
    if(cast - num < 0)
        return cast + 1;
    return cast;
}

long abs_negative(long value) {
    return value < 0 ? -value : 0;
}

Array_Array_pixel get_columns_raw(image_data image, long loc_width, long loc_height, long init_x, long init_y, _Bool cut, _Bool clockwise) {
    if (loc_width < 0 || loc_height < 0 || init_x < 0 || init_y < 0)
        exit(40);
    Array_Array_pixel columns = create_Array_pixel_array(pixel_columns_deleter);
    pixel **pixel_rows = (pixel**)image.rows;
    pixel black = { .0, .0, .0 };

    if (clockwise) {
        for (long i = init_x; i < loc_width; ++i) {
            Array_pixel column = create_pixel_array(NULL);
            for (long j = min(loc_height - 1, image.height - 1); j >= init_y; --j) {
                add_pixel_element(&column, pixel_rows[j][i]);
                if (cut)
                    pixel_rows[j][i] = black;
            }
            add_Array_pixel_element(&columns, column);
        }
    } else {
        for (long i = min(loc_width - 1, image.width - 1); i >= init_x; --i) {
            Array_pixel column = create_pixel_array(NULL);
            for (long j = init_y; j < loc_height; ++j) {
                add_pixel_element(&column, pixel_rows[j][i]);
                if (cut)
                    pixel_rows[j][i] = black;
            }
            add_Array_pixel_element(&columns, column);
        }
    }
    return columns;
}

Array_Array_pixel get_columns(Array_Array_pixel rows, long init_x, long init_y, _Bool cut, _Bool clockwise) {

    if (!rows.size) return create_Array_pixel_array(pixel_columns_deleter);
    pixel** byte_rows = malloc(sizeof (pixel*) * rows.size);
    for (int i = 0; i < rows.size; byte_rows[i] = rows.arr[i].arr, ++i);
    image_data data = { .rows = byte_rows, .height = rows.size, .width = rows.arr[0].size };
    Array_Array_pixel ret_arr = get_columns_raw(data, rows.arr[0].size, rows.size, init_x, init_y, cut, clockwise);
    free(byte_rows);
    return ret_arr;
}

void color_row(pixel *row, pixel RGB, long stop, long width) {
    stop = min(stop, width - 1);
    for(long i = 0; i <= stop; i++) {
        row[i] = RGB;
    }
}
