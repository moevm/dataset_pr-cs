//
// Created by zoomie on 5/22/24.
//

#include "edge_alina.h"
#include <png.h>
#include "image_data.h"
#include "utils.h"

_Bool compare_pixels(pixel* a, pixel b) {
    if(a && a->R == b.R && a->G == b.G && a->B == b.B)
        return 1;
    return 0;
}

pixel** eight_hateful(image_data image, pixel color, pixel fill_color,  int x, int y) {
    pixel* one = NULL, *two = NULL, *three = NULL, *four = NULL, *five= NULL, *six = NULL, *seven= NULL, *eight= NULL;

    int i = x;
    int j = y;

    if(&image.rows[i-1] && &image.rows[i-1][j-1]) {
        one = &image.rows[i - 1][j - 1];
        if(!(compare_pixels(one, color)))
            *one = fill_color;
    }

    if(&image.rows[i-1]) {
        two = &image.rows[i - 1][j];
        if(!(compare_pixels(two, color)))
            *two = fill_color;
    }

    if(&image.rows[i-1] && &image.rows[i-1][j+1]) {
        three = &image.rows[i - 1][j + 1];
        if (!(compare_pixels(three, color)))
            *three = fill_color;
    }

    if(&image.rows[i][j-1]) {
        four = &image.rows[i][j - 1];
        if(!(compare_pixels(four, color)))
            *four = fill_color;
    }

    if(&image.rows[i][j+1]) {
        five = &image.rows[i][j + 1];
        if (!(compare_pixels(five, color)))
            *five = fill_color;
    }

    if(&image.rows[i+1] && &image.rows[i+1][j-1]) {
        six = &image.rows[i + 1][j - 1];
        if(!(compare_pixels(six, color)))
            *six = fill_color;
    }

    if(&image.rows[i+1]) {
        seven = &image.rows[i + 1][j];
        if(!(compare_pixels(seven, color)))
            *seven = fill_color;
    }

    if(&image.rows[i+1] && &image.rows[i+1][j+1]) {
        eight = &image.rows[i + 1][j + 1];
        if(!(compare_pixels(eight, color)))
            *eight = fill_color;
    }

    return image.rows;
}
png_bytepp edge_alina(image_data image, pixel color, pixel fill_color) {
    for(int i = 0; i < image.height; i++) {
        for(int j = 0; j < image.width; j++) {
            if(compare_pixels(&image.rows[i][j], color))
                image.rows = eight_hateful(image, color, fill_color, i, j);
        }
    }
    return (png_bytepp)image.rows;
}
