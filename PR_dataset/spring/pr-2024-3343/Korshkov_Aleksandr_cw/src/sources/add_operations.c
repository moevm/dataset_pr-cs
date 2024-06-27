#include "../include/add_operations.h"

/* проверка, что строка является числом */
int is_digit(char *line) {
    if (strlen(line) == 0) {
        return 0;
    }
    if (line[0] == '-') {
        if (is_digit(line + 1)) {
            return 1;
        } else {
            return 0;
        }
    }
    for (int i = 0; i < strlen(line); i++) {
        if (!isdigit(line[i])) {
            return 0;
        }
    }
    return 1;
}

/* освобождение памяти от изображения */
void free_png(Png *png) {
    int y;
    for (y = 0; y < png->height; y++)
        free(png->row_pointers[y]);
    free(png->row_pointers);
    png_destroy_read_struct(&png->png_ptr, &png->info_ptr, NULL);
}

void set_pixel(int x, int y, RGB color, Png *png) {
    if (x >= 0 && x < png->width && y >= 0 && y < png->height) {
        png_byte *ptr = &(png->row_pointers[y][x * get_size_pixel(png)]);
        ptr[0] = color.r;
        ptr[1] = color.g;
        ptr[2] = color.b;
    }
}

RGB get_color(int x, int y, Png *png) {
    png_byte *ptr = &(png->row_pointers[y][x * get_size_pixel(png)]);
    if (x >= 0 && x < png->width && y >= 0 && y < png->height) {
        RGB color = {.r=ptr[0], .g=ptr[1], .b=ptr[2]};
        return color;
    }
}

int get_size_pixel(Png *png) {
    int size_pixel = 0;
    if (png->color_type == PNG_COLOR_TYPE_RGB)
        size_pixel = 3;
    else if (png->color_type == PNG_COLOR_TYPE_RGBA)
        size_pixel = 4;
    return size_pixel;
}


