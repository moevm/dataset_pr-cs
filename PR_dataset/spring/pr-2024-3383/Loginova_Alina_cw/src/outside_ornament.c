//
// Created by zoomie on 5/22/24.
//

extern long width, height;
#include "outside_ornament.h"
#include "arrays.h"
#include <stdlib.h>
#include <string.h>
#include "utils.h"

Array_Array_pixel add_top_rows(image_data image, Array_Array_pixel rows, pixel color) {

    for(long i = 0; i < height; i++) {
        Array_pixel row = create_pixel_array(NULL);
        for(long j = 0; j < width; j++) {
            add_pixel_element(&row, color);
        }
    }
    return rows;
}

png_bytepp outside_ornament(image_data image, pixel color, long thickness) {

    width = thickness * 2 + image.width;
    height = thickness * 2 + image.height;

    pixel** new_rows = (pixel**)malloc(height * sizeof(pixel*));
    for(int i = 0; i < height; i++) {
        new_rows[i] = malloc(width * sizeof(pixel));
        color_row(new_rows[i], color, width, width);
    }

    for(int i = 0; i < image.height; i++) {
        memcpy(&new_rows[i + thickness][thickness], image.rows[i], image.width * 3);
    }

    return (png_bytepp)new_rows;
}
