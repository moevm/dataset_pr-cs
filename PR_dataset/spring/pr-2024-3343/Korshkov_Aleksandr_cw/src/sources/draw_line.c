#include "../include/draw_line.h"

/* функция для рисования линия */
void draw_line(int x0, int y0, int x1, int y1, int thickness, RGB color, Png *png) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;
    while (1) {
        int rectX = x0 - thickness / 2;
        int rectY = y0 - thickness / 2;
        int rectWidth = thickness;
        int rectHeight = thickness;
        if ((rectX >= 0 && rectX + rectWidth < png->width && rectY >= 0 && rectY + rectHeight < png->height) ||
            (x0 >= 0 && x0 < png->width && y0 >= 0 && y0 < png->height)) {
            for (int y = rectY; y < rectY + rectHeight; ++y) {
                for (int x = rectX; x < rectX + rectWidth; ++x) {
                    set_pixel(x, y, color, png);
                }
            }
        }
//            set_square(x0, y0, thickness / 2, color, png);
//            draw_fill_circle(x0, y0, thickness / 2, color, png);
        if (x0 == x1 && y0 == y1) {
            break;
        }
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

/* проверка введённых параметров для линии на существование (все ли существуют) */
int check_line(info_line *line) {
    if (line->p0.x == -1 || line->p0.y == -1) {
        puts("You don't specify start cords of line!"); /* нет начальных координат */
        return 0;
    }
    if (line->p1.x == -1 || line->p1.y == -1) {
        puts("You don't specify end cords of line!"); /* нет конечных координат */
        return 0;
    }
    if (line->color.r == -1 || line->color.g == -1 || line->color.b == -1) {
        puts("You don't specify color of line!"); /* нет конечных координат */
        return 0;
    }
    if (line->thickness == -1) {
        puts("You don't specify thickness of line!"); /* нет толщины */
        return 0;
    }
    return 1;
}

/* функция для задания начальных координат */
void set_start_cords(char *xy, info_line *line) {
    char *x = strtok(xy, ".");
    char *y = strtok(NULL, ".");
    if (x == NULL) {
        puts("You don't specify X for start point of line!");
        exit(40);
    }
    if (y == NULL) {
        puts("You don't specify Y for start point of line!");
        exit(40);
    }
    if (is_digit(x))
        line->p0.x = atoi(x);
    if (is_digit(y))
        line->p0.y = atoi(y);
    else {
        puts("Your Y coord for start point isn't integer number!");
        exit(41);
    }
}

/* функция для задания конечных координат */
void set_end_cords(char *xy, info_line *line) {
    char *x = strtok(xy, ".");
    char *y = strtok(NULL, ".");
    if (x == NULL) {
        puts("You don't specify X for end point of line!");
        exit(40);
    }
    if (y == NULL) {
        puts("You don't specify Y for end point of line!");
        exit(40);
    }
    if (is_digit(x))
        line->p1.x = atoi(x);
    else {
        puts("Your X coord for end point isn't integer number!");
        exit(41);
    }
    if (is_digit(y))
        line->p1.y = atoi(y);
    else {
        puts("Your Y coord for end point isn't integer number!");
        exit(41);
    }
}

/* функция для задания цвета линии */
void set_color_line(char *rgb, info_line *line) {
    char *r = strtok(rgb, ".");
    char *g = strtok(NULL, ".");
    char *b = strtok(NULL, ".");
    if (r == NULL) {
        puts("You don't specify R (red) component of line's color!");
        exit(40);
    }
    if (g == NULL) {
        puts("You don't specify G (green) component of line's color!");
        exit(40);
    }
    if (b == NULL) {
        puts("You don't specify B (blue) component of line's color!");
        exit(40);
    }
    if (is_digit(r)) {
        if ((atoi(r) < 0) || (atoi(r) > 255)) {
            puts("Your R (red) component of line's color must be in the range from 0 to 255!");
            exit(42);
        }
        line->color.r = atoi(r);
    } else {
        puts("Your R (red) component of line's color isn't integer number!");
        exit(41);
    }
    if (is_digit(g)) {
        if ((atoi(g) < 0) || (atoi(g) > 255)) {
            puts("Your G (green) component of line's color must be in the range from 0 to 255!");
            exit(42);
        }
        line->color.g = atoi(g);
    } else {
        puts("Your G (green) component of line's color isn't integer number!");
        exit(41);
    }
    if (is_digit(b)) {
        if ((atoi(b) < 0) || (atoi(b) > 255)) {
            puts("Your B (blue) component of line's color must be in the range from 0 to 255!");
            exit(42);
        }
        line->color.b = atoi(b);
    } else {
        puts("Your B (blue) component of line's color isn't integer number!");
        exit(41);
    }
}

/* функция для задания толщины линии */
void set_thickness_line(char *thickness, info_line *line) {
    if (thickness == NULL) {
        printf("You don't specify thickness of line!\n");
        exit(40);
    }
    if (is_digit(thickness)) {
        if (atoi(thickness) < 1) {
            printf("Your line's thickness must be greater than 0!\n");
            exit(42);
        }
        line->thickness = atoi(thickness);
    } else {
        printf("Your line's thickness isn't integer number!\n");
        exit(41);
    }
}


void draw_circle(int x0, int y0, int radius, int thickness, RGB color, Png *png) {
    int yCenter = y0;
    int halfThickness = thickness / 2;
    int outerRadius = radius + halfThickness;
    int innerRadius = radius - halfThickness;
    int outerRadiusSquared = outerRadius * outerRadius;
    int innerRadiusSquared = innerRadius * innerRadius;
    for (int y = yCenter - outerRadius; y <= yCenter + outerRadius; y++) {
        for (int x = x0 - outerRadius; x <= x0 + outerRadius; x++) {
            if (x >= 0 && x < png->width && y >= 0 && y < png->height) {
                int dx = x - x0;
                int dy = y - y0;
                int distance = dx * dx + dy * dy;
                if (distance <= outerRadiusSquared && distance >= innerRadiusSquared) {
                    set_pixel(x, y, color, png);
                }
            }
        }
    }
}

void draw_fill_circle(int x0, int y0, int radius, RGB color, Png *png) {
    int radiusSquared = radius * radius;
    for (int y = y0 - radius; y <= y0 + radius; y++) {
        for (int x = x0 - radius; x <= x0 + radius; x++) {
            int dx = x - x0;
            int dy = y - y0;
            int distance = dx * dx + dy * dy;
            if (distance <= radiusSquared)
                set_pixel(x, y, color, png);
        }
    }
}

void set_square(int x0, int y0, int size, RGB color, Png *png) {
    for (int i = -size; i <= size; i++) {
        for (int j = -size; j <= size; j++) {
            set_pixel(x0 + i, y0 + j, color, png);
        }
    }
}

