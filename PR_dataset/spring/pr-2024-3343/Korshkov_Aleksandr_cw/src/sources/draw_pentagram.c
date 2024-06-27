#include "../include/draw_pentagram.h"

void draw_pentagram(int x0, int y0, int radius, int thickness, RGB color, Png *png) {
    draw_circle(x0, y0, radius, thickness, color, png);
    Point p2 = {x0, y0 - radius};
    Point p5 = {x0 + radius * cos(-18 * M_PI / 180), y0 + radius * sin(-18 * M_PI / 180)};
    Point p3 = {x0 + radius * cos(54 * M_PI / 180), y0 + radius * sin(54 * M_PI / 180)};
    Point p1 = {x0 + radius * cos(126 * M_PI / 180), y0 + radius * sin(126 * M_PI / 180)};
    Point p4 = {x0 + radius * cos(198 * M_PI / 180), y0 + radius * sin(198 * M_PI / 180)};
    draw_line(p1.x, p1.y, p2.x, p2.y, thickness, color, png);
    draw_line(p2.x, p2.y, p3.x, p3.y, thickness, color, png);
    draw_line(p3.x, p3.y, p4.x, p4.y, thickness, color, png);
    draw_line(p4.x, p4.y, p5.x, p5.y, thickness, color, png);
    draw_line(p5.x, p5.y, p1.x, p1.y, thickness, color, png);
}

int check_pentagram(info_pentagram *pentagram) {
    if (!pentagram->radius) {
        puts("You don't specify radius of pentagram!");
        return 0;
    }
    if (!pentagram->center.x || !pentagram->center.y) {
        puts("You don't specify center of pentagram!");
        return 0;
    }
    if (!pentagram->thickness) {
        puts("You don't specify thickness of pentagram!");
        return 0;
    }
    return 1;
}

void set_radius(char *radius, info_pentagram *pentagram) {
    if (radius == NULL) {
        printf("You don't specify radius of pentagram!\n");
        exit(41);
    }
    if (is_digit(radius)) {
        if (atoi(radius) < 1) {
            printf("Your pentagram's radius must be greater than 0!\n");
            exit(42);
        }
        pentagram->radius = atoi(radius);
    } else {
        printf("Your pentagram's radius isn't an integer number!\n");
        exit(0);
    }
}

void set_center(char *center, info_pentagram *pentagram) {
    char *x = strtok(center, ".");
    char *y = strtok(NULL, ".");
    if (x == NULL) {
        puts("You don't specify X for center of pentagram!");
        exit(40);
    }
    if (y == NULL) {
        puts("You don't specify Y for center of pentagram!");
        exit(40);
    }
    if (is_digit(x))
        pentagram->center.x = atoi(x);
    else {
        puts("Your X coord for pentagram's center isn't integer number!");
        exit(41);
    }
    if (is_digit(y))
        pentagram->center.y = atoi(y);
    else {
        puts("Your Y coord for pentagram's center isn't integer number!");
        exit(41);
    }
}

void set_thickness_pentagram(char *thickness, info_pentagram *pentagram) {
    if (thickness == NULL) {
        printf("You don't specify thickness of pentagram!\n");
        exit(40);
    }
    if (is_digit(thickness)) {
        if (atoi(thickness) < 1) {
            printf("Your line's thickness must be greater than 0!\n");
            exit(42);
        }
        pentagram->thickness = atoi(thickness);
    } else {
        printf("Your pentagram's thickness isn't integer number!\n");
        exit(40);
    }
}

void set_color_pentagram(char *rgb, info_pentagram *pentagram) {
    char *r = strtok(rgb, ".");
    char *g = strtok(NULL, ".");
    char *b = strtok(NULL, ".");
    if (r == NULL) {
        puts("You don't specify R (red) component of pentagram's color!");
        exit(40);
    }
    if (g == NULL) {
        puts("You don't specify G (green) component of pentagram's color!");
        exit(40);
    }
    if (b == NULL) {
        puts("You don't specify B (blue) component of pentagram's color!");
        exit(40);
    }
    if (is_digit(r)) {
        if ((atoi(r) < 0) || (atoi(r) > 255)) {
            puts("Your R (red) component of pentagram's color must be in the range from 0 to 255!");
            exit(41);
        }
        pentagram->color.r = atoi(r);
    } else {
        puts("Your R (red) component of pentagram's color isn't integer number!");
        exit(41);
    }
    if (is_digit(g)) {
        if ((atoi(g) < 0) || (atoi(g) > 255)) {
            puts("Your G (green) component of pentagram's color must be in the range from 0 to 255!");
            exit(41);
        }
        pentagram->color.g = atoi(g);
    } else {
        puts("Your G (green) component of pentagram's color isn't integer number!");
        exit(41);
    }
    if (is_digit(b)) {
        if ((atoi(b) < 0) || (atoi(b) > 255)) {
            puts("Your B (blue) component of pentagram's color must be in the range from 0 to 255!");
            exit(41);
        }
        pentagram->color.b = atoi(b);
    } else {
        puts("Your B (blue) component of pentagram's color isn't integer number!");
        exit(41);
    }
}