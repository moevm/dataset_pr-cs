#include "../include/draw_mirror.h"

/* функция отражения области */
void draw_mirror(int x0, int y0, int x1, int y1, char axis, Png *png) {
    int width = abs(x1 - x0);
    int height = abs(y1 - y0);
    if (axis == 'x') {
        for (int y = y0; y <= y1; ++y) {
            for (int x = x0; x < x0 + width / 2; ++x) {
                int mirroredX = x1 - (x - x0);
                RGB tempColor = get_color(x, y, png);
                RGB newColor = get_color(mirroredX, y, png);
                set_pixel(x, y, newColor, png);
                set_pixel(mirroredX, y, tempColor, png);
            }
        }
    } else if (axis == 'y') {
        for (int y = y0; y < y0 + height / 2; ++y) {
            for (int x = x0; x <= x1; ++x) {
                int mirroredY = y1 - (y - y0);
                RGB tempColor = get_color(x, y, png);
                RGB newColor = get_color(x, mirroredY, png);
                set_pixel(x, y, newColor, png);
                set_pixel(x, mirroredY, tempColor, png);
            }
        }
    }
}


int check_mirror(info_mirror *mirror) {
    if (mirror->p0.x == -1 || mirror->p0.y == -1) {
        puts("You don't specify start cords of mirror's edge!");
        return 0;
    }
    if (mirror->p1.x == -1 || mirror->p1.y == -1) {
        puts("You don't specify end cords of mirror's edge!");
        return 0;
    }
    if (mirror->axis == 'n') {
        puts("You don't specify axis of mirror!");
        return 0;
    }
    return 1;
}

void set_left_up(char *xy, info_mirror *mirror) {
    char *x = strtok(xy, ".");
    char *y = strtok(NULL, ".");
    if (x == NULL) {
        puts("You don't specify X for left_up point of mirror's edge!");
        exit(40);
    }
    if (y == NULL) {
        puts("You don't specify Y for left_up point of mirror's edge!");
        exit(40);
    }
    if (is_digit(x))
        mirror->p0.x = atoi(x);
    else {
        puts("Your X coord for left_up point isn't integer number!");
        exit(41);
    }
    if (is_digit(y)) {
        mirror->p0.y = atoi(y);
    } else {
        puts("Your Y coord for left_up point isn't integer number!");
        exit(41);
    }
}

void set_right_down(char *xy, info_mirror *mirror) {
    char *x = strtok(xy, ".");
    char *y = strtok(NULL, ".");
    if (x == NULL) {
        puts("You don't specify X for right_down point of mirror's edge!");
        exit(40);
    }
    if (y == NULL) {
        puts("You don't specify Y for right_down point of mirror's edge!");
        exit(40);
    }
    if (is_digit(x))
        mirror->p1.x = atoi(x);
    else {
        puts("Your X coord for right_down point isn't integer number!");
        exit(41);
    }
    if (is_digit(y)) {
        mirror->p1.y = atoi(y);
    } else {
        puts("Your Y coord for right_down point isn't integer number!");
        exit(41);
    }
}

void set_axis(char *axis, info_mirror *mirror) {
    if (strcmp(axis, "x") == 0) {
        mirror->axis = 'x';
    } else if (strcmp(axis, "y") == 0) {
        mirror->axis = 'y';
    } else {
        puts("Your axis isn't 'x' or 'y'!");
        exit(41);
    }
}