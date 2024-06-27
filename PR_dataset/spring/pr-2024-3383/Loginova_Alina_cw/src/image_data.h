#ifndef CW_PR_2024_IMAGE_DATA_H
#define CW_PR_2024_IMAGE_DATA_H

typedef struct pixel {
    unsigned char R, G, B;
} pixel;

typedef struct image_data {
    pixel** rows;
    long height;
    long width;
} image_data;

typedef struct pixel_point {
    long x, y;
} pixel_point;

#endif
