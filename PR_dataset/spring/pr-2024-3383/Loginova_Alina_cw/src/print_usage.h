#ifndef CW_PRINT_USAGE_H
#define CW_PRINT_USAGE_H
#define USAGE "Usage:\n[--split --number_x <arg> --number_y <arg> --thickness <arg> --color <arg> <file_name>]\n\
Splits a picture, number_x and number_y must be greater than 1.\n\n\
[--rect --left_up <arg> --right_down <arg> --thickness <arg> --color <arg> --fill --fill_color <arg> <file_name>]\n\
Draws a rectangle on the picture.\n\n\
[--ornament --pattern rectangle circle semicircles --color <arg> --thickness <arg> --count <arg> [other ornaments] <file_name>]\n\
Draws an ornament using the specified pattern (rectangle, circle, semicircle.\n\n\
[--rotate --left_up <arg> --right_down <arg> --angle <arg> <file_name>]\n\
Rotates the picture by 90, 180, or 270 degrees\n\n\
[--info]\n\
Prints info about the picture.\n"

    void print_usage();

#endif
