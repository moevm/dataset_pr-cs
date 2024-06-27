#include "ornament.h"
#include <string.h>
#include "rect.h"
#include "utils.h"
#include <math.h>
#include <stdlib.h>
const char circle[]      = "circle",
        rectangle[]   = "rectangle",
        semicircles[] = "semicircles";

png_bytepp print_circle(long center_x, long center_y, long radius, long thickness, pixel color, image_data image);
png_bytepp circle_ornament(pixel color, image_data image);
png_bytepp semicircles_ornament(long count, pixel color, long thickness, image_data image);
png_bytepp rect_ornament(long thickness, long count, pixel RGB, image_data image);

png_bytepp ornament(char *pattern, long count, pixel RGB, long thickness, image_data image) {
    if (!strcmp(pattern, circle))
        return circle_ornament(RGB, image);
    else if (!strcmp(pattern, rectangle))
        return rect_ornament(thickness, count, RGB, image);
    else if (!strcmp(pattern, semicircles))
        return semicircles_ornament(count, RGB, thickness, image);
    else
        printf("[call_ornament()]: указан неподдерживаемый паттерн, выберите один из: circle, rectangle, semicircles.\n");
}

png_bytepp circle_ornament(pixel color, image_data image) {
    long center_x = (image.width - 1) / 2,
            center_y = (image.height - 1) / 2;

    long rad = min(image.width, image.height) / 2 + 1;
    long thickness = ceilf(sqrtf((image.width + ((image.width + 1) % 2)) * (image.width + ((image.width + 1) % 2)) +
                                 (image.height + ((image.height + 1) % 2)) * (image.height + ((image.height + 1) % 2))) / 2) - rad + 1;

    return print_circle(center_x, center_y, rad + thickness / 2, thickness, color, image);
}

png_bytepp rect_ornament(long thickness, long count, pixel RGB, image_data image) {
    long left_up_x = 0, left_up_y = 0, right_down_x = image.width - 1, right_down_y = image.height - 1, x_center = image.width / 2, y_center = image.height / 2;

    /* заглушка для рисования паттерна без заливки */
    pixel RGB_f = { 0, 0, 0 };

    for(int i = 0; i < count; i++) {
        image.rows = (pixel**)rect(left_up_x, left_up_y, right_down_x, right_down_y, thickness - 1, RGB, NULL, RGB_f, image, 1);
        left_up_x += 2 * thickness;
        left_up_y += 2 * thickness;
        right_down_x -= 2 * thickness;
        right_down_y -= 2 * thickness;
        if (left_up_x + thickness > x_center || left_up_y + thickness > y_center)
            break;
    }
    return (png_bytepp)image.rows;
}

png_bytepp semicircles_ornament(long count, pixel color, long thickness, image_data image) {
//    long diameter = floorf((float)(image.width / count)),
//        diff = image.width - count * diameter,
//        diameter_x = diameter + diff;
//
//    diameter = floorf((float)(image.height / count));
//    diff = image.height - count * diameter;
//
//    long diameter_y = diameter + diff,

//    long diameter_x = ceilf((float)(image.width + count - 1) / count),
//            diameter_y = ceilf((float)(image.height + count - 1) / count),

    long diameter_x = (image.width + count - 1) % count
                    ? (image.width + count - 1 + ((image.width + count - 1) % count)) / count
                    : (image.width + count - 1) / count,
         diameter_y = (image.height + count - 1) % count
                    ? (image.height + count - 1 + ((image.height + count - 1) % count)) / count
                    : (image.height + count - 1) / count,
         radius_x = diameter_x / 2 + 1,
         radius_y = diameter_y / 2 + 1;

    if(radius_x <= 1 || radius_y <= 1) {
        printf("Неверное значение аргумента count\n");
        exit(40);
    }

    long i = radius_x - 1;
    do {
        print_circle(i, 0, radius_x, thickness, color, image);
        print_circle(i, image.height - 1, radius_x, thickness, color, image);
        i += (radius_x - 1) * 2 /*- (thickness + 1) % 2 если надо совместить круги четной толщины */;
    } while (i < image.width + radius_x);

    i = radius_y - 1;
    do {
        print_circle(0, i, radius_y, thickness, color, image);
        print_circle(image.width - 1, i, radius_y, thickness, color, image);
        i += (radius_y - 1) * 2 /*- (thickness + 1) % 2 если надо совместить круги четной толщины */;
    } while (i < image.height + radius_y);
    return (png_bytepp)image.rows;
}

png_bytepp print_circle(long center_x, long center_y, long radius, long thickness, pixel color, image_data image) {
    int thickness_quot = (thickness - 1) / 2,
            thickness_rem  = (thickness - 1) % 2;

    long root_x = center_x - radius + 1 - thickness_rem - thickness_quot,
            root_y = center_y - radius + 1 - thickness_rem - thickness_quot;

    for (long y = clamp_positive(root_y); y < min(root_y + (radius + thickness_rem + thickness_quot) * 2, image.height); ++y)
        for (long x = clamp_positive(root_x); x < min(root_x + (radius + thickness_rem + thickness_quot) * 2, image.width); ++x) {
            float distance = roundf(sqrtf((abs(center_y - y) + 1) * (abs(center_y - y) + 1) +
                                          (abs(center_x - x) + 1) * (abs(center_x - x) + 1)));
            if (distance <= radius + thickness_quot + thickness_rem && distance >= radius - thickness_quot)
                image.rows[y][x] = color;
        }
    return (png_bytepp)image.rows;
}
