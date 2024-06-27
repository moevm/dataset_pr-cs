//
// Created by zoomie on 5/22/24.
//

#include "tiles.h"
#include <png.h>
#include "image_data.h"
#include "stdlib.h"
#include "utils.h"
#include "string.h"

extern long height, width;

long max(long a, long b) {
    if(a > b)
        return a;
    return b;
}

png_bytepp put_string(image_data image, png_bytep row, png_bytep row_to_put) {
    long bytes = width * 3;
    long width_count = image.width / width;
    long k = 0;
    for(long i = 0; i < width_count; i++, k+=width*3) {
        memcpy(&row[k], row_to_put, bytes);
    }

    memcpy(&row[k], row_to_put, (image.width - width * width_count) * 3);
}

png_bytepp put_picture(image_data image, png_bytepp rows, png_bytepp rows_to_put) {

    for(long i = 0; i < height; i++) {
        put_string(image, rows[i], rows_to_put[i]);
    }

    return (png_bytepp)image.rows;
}

png_bytepp tiles(image_data image, long left_up_x, long left_up_y, long right_down_x, long right_down_y) {

    height = right_down_y - left_up_y;
    width =  right_down_x - left_up_x;

    pixel** new_rows = (pixel**)malloc(height * sizeof(pixel*));
    for(int i = 0; i < height; i++) {
        new_rows[i] = malloc(width * sizeof(pixel));
    }

    for(int i = 0; i < height; i++) {
        pixel* row_ptr = &image.rows[left_up_y++][left_up_x];
        memcpy(&new_rows[i][0], row_ptr, width * 3);
    }

    long height_count = image.height / height;
    long k = 0;
    for(long i = 0; i < height_count; i++, k+=height) {
        put_picture(image, (png_bytepp)&image.rows[k], (png_bytepp)new_rows);
    }

    height = image.height - height_count * height;
    put_picture(image, (png_bytepp)&image.rows[k], (png_bytepp)new_rows);

    height = image.height;
    width = image.width;
    return (png_bytepp)image.rows;
}
