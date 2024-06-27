#include "toolkit.h"

#define MAX_COLOR_VALUE 255

int cmp_color(Rgb first, Rgb second)
{
    if (first.r == second.r && first.g == second.g && first.b == second.b)
        return 1;
    return 0;
}

void set_pixel(Image *image, int x, int y, Rgb color)
{
    if (x >= 0 && y >= 0 && x < image->width && y < image->height)
        image->pix[x][y] = color;
}

int get_number(char *ptr)
{
    for (int i = 0; i < strlen(ptr); i++)
    {
        if (isdigit(ptr[i]) == 0)
        {
            print_error_and_exit("error: value must be a non-negative digit");
        }
    }
    int tmp = atoi(ptr);
    if (tmp >= 0)
    {
        return tmp;
    }
    else
    {
        print_error_and_exit("error: value must be a non-negative digit");
    }
}

Rgb get_color_arg(char *str)
{
    Rgb color;
    char *token = strtok(str, ".");
    int index = 0;
    while (token != NULL)
    {
        int t = get_number(token);
        if (t > MAX_COLOR_VALUE)
        {
            print_error_and_exit("error: invalid color input");
        }
        else
        {
            if (index == 0)
            {
                color.r = t;
            }
            else if (index == 1)
            {
                color.g = t;
            }
            else
            {
                color.b = t;
            }
            index++;
            token = strtok(NULL, ".");
        }
    }
    if (index > 3)
    {
        print_error_and_exit("error: invalid color input or RGBA");
    }
    return color;
}

void print_error_and_exit(const char *error_message) {
    fprintf(stderr, "%s", error_message);
    exit(ERROR_CODE);
}