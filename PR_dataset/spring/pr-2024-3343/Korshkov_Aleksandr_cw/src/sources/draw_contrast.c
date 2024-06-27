#include "../include/draw_contrast.h"

void set_alpha(char *alpha, info_contrast *contrast) {
    if (alpha == NULL) {
        printf("You don't specify alpha!\n");
        exit(40);
    }
    if (atof(alpha) > 0) {
        contrast->alpha = atof(alpha);
    } else {
        printf("Alpha must be greater than 0!\n");
        exit(45);
    }
    contrast->alpha = atof(alpha);
}

void set_beta(char *beta, info_contrast *contrast) {
    if (beta == NULL) {
        printf("You don't specify beta!\n");
        exit(40);
    }
    if (is_digit(beta)) {
        contrast->beta = atoi(beta);
    } else {
        printf("Your beta isn't integer number!\n");
        exit(41);
    }
}

void set_contrast(info_contrast *contrast, Png *png) {
    for (int y = 0; y < png->height; y++) {
        for (int x = 0; x < png->width; x++) {
            RGB color_pixel = get_color(x, y, png);
            RGB new_color = {.r=(int) (contrast->alpha * color_pixel.r + contrast->beta),
                    .g=(int) (contrast->alpha * color_pixel.g + contrast->beta),
                    .b=(int) (contrast->alpha * color_pixel.b + contrast->beta)};
            if (new_color.r > 255) {
                new_color.r = 255;
            }
            if (new_color.g > 255) {
                new_color.g = 255;
            }
            if (new_color.b > 255) {
                new_color.b = 255;
            }
            set_pixel(x, y, new_color, png);
        }
    }
}