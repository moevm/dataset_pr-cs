#include "errors.h"
#include "bmp.h"
#include "pixels.h"
#include <stdio.h>
#include <stdlib.h>

void raise_error(const char* message, int error_code)
{
    printf("Error: %s\n", message);
    print_help();
    exit(error_code);
}

void check_sscanf(int result, int expected)
{
    if (result != expected) {
        raise_error("incorrect params", READ_VALUE_ERR);
    }
}

void check_crop_params(unsigned int w, unsigned int h, point_t* left_up, point_t* right_down)
{
    if (left_up->x > w || left_up->y > h || left_up->x > right_down->x || left_up->y > right_down->y)
        raise_error("incorrect point value", POINT_ERR);
    if (left_up->x < 0)
        left_up->x = 0;
    if (left_up->y < 0)
        left_up->y = 0;
    if (right_down->x > w)
        right_down->x = w;
    if (right_down->y > h)
        right_down->y = h;
    if (left_up->x == right_down->x)
        (right_down->x)++;
    if (left_up->y == right_down->y)
        (right_down->y)++;
}

void check_thickness(int thickness)
{
    if (thickness < 0) {
        raise_error("incorrect thickness value", THICKNESS_ERR);
    }
}