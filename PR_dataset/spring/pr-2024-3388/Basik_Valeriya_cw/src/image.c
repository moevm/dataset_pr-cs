#include "image.h"
#include <math.h>

void print_help()
{
    printf("Course work for option 4.2, created by Basik Valeria\n");
    puts("Изображение должно быть в формате BMP\n"
         "По умолчанию последним аргументом утилите должно передаваться имя входного файла\n"
         "Команды:\n"
         "  --color_replace - Заменяет все пиксели заданного цвета на другой цвет. Флаги: --old_color(цвет задаётся строкой `rrr.ggg.bbb`), --new_color\n"
         "  --rgbfilter - Устанавливает значение в диапазоне от 0 до 255 для заданной компоненты. Флаги: --component_name(red, green, blue), --component_value\n"
         "  --split - Разделяет изображение на N*M частей. Flags: --color, --number_x, --number_y, --thickness\n"
         "  -h, --help - показать справку.\n"
         "  --info вывести информацию о входном изображении \n"
         "\n");
}

void change_color(Image *image, Rgb old_color, Rgb new_color)
{
    for (int x = 0; x < image->width; x++)
    {
        for (int y = 0; y < image->height; y++)
        {
            if (cmp_color(image->pix[x][y], old_color))
                set_pixel(image, x, y, new_color);
        }
    }
}

void apply_rgb_filter(Image *image, int component, int value)
{
    if (0 > value || 255 < value)
    {
        print_error_and_exit(ERROR_INVAlID_COLOR);
    }

    for (int x = 0; x < image->width; x++)
    {
        for (int y = 0; y < image->height; y++)
        {
            Rgb old_color = image->pix[x][y];
            switch (component)
            {
            case 0:
                old_color.r = value;
                break;
            case 1:
                old_color.g = value;
                break;
            case 2:
                old_color.b = value;
                break;
            }
            set_pixel(image, x, y, old_color);
        }
    }
}

void set_circle_pixels(Image *image, int x_center, int y_center, int x, int y, Rgb color)
{
    set_pixel(image, x_center + x, y_center + y, color);
    set_pixel(image, x_center + x, y_center - y, color);
    set_pixel(image, x_center - x, y_center + y, color);
    set_pixel(image, x_center - x, y_center - y, color);
    set_pixel(image, x_center + y, y_center + x, color);
    set_pixel(image, x_center + y, y_center - x, color);
    set_pixel(image, x_center - y, y_center + x, color);
    set_pixel(image, x_center - y, y_center - x, color);
}

void draw_circle_dot_pixels(Image *image, int x_center, int y_center, Rgb color)
{
    set_pixel(image, x_center, y_center, color);
    set_pixel(image, x_center + 1, y_center, color);
    set_pixel(image, x_center, y_center + 1, color);
    set_pixel(image, x_center - 1, y_center, color);
    set_pixel(image, x_center, y_center - 1, color);
}

void draw_circle_two_dot_pixels(Image *image, int x_center, int y_center, Rgb color)
{
    set_pixel(image, x_center + 1, y_center + 1, color);
    set_pixel(image, x_center + 1, y_center - 1, color);
    set_pixel(image, x_center - 1, y_center + 1, color);
    set_pixel(image, x_center - 1, y_center - 1, color);
    set_pixel(image, x_center + 2, y_center, color);
    set_pixel(image, x_center, y_center + 2, color);
    set_pixel(image, x_center - 2, y_center, color);
    set_pixel(image, x_center, y_center - 2, color);
}

void draw_circle_field(Image* input, int x_center, int y_center, int radius, Rgb color) {
    if (radius == 0) radius = 1;

    if (radius == 1 || radius == 2) {
        draw_circle_dot_pixels(input, x_center, y_center, color);

        if (radius==2) {
            draw_circle_two_dot_pixels(input, x_center, y_center, color);
        }

        return;
    }
   
    int x = 0;
    int y = radius;
    int delta = 1 - 2 * radius;
    int error = 0;

    while (y >= x) {
        set_circle_pixels(input, x_center, y_center, x, y, color);
        error = 2 * (delta + y) - 1;
        if ((delta < 0) && (error <= 0)) {
            delta += 2 * (++x) + 1;
            continue;
        }
        if ((delta > 0) && (error > 0)) {
            delta -= 2 * (--y) + 1;
            continue;
        }
        delta += 2 * ((++x) - (--y));
    }

    draw_circle_field(input, x_center, y_center, radius/2, color);
}

void draw_line(Image* input,
               Rgb color,
               int thickness,
               int x_start,
               int y_start,
               int x_end,
               int y_end) {
    int delta_x = abs(x_end - x_start);
    int delta_y = abs(y_end - y_start);
    int sign_x = x_start < x_end ? 1 : -1;
    int sign_y = y_start < y_end ? 1 : -1;
    int second_error;
    int first_error = delta_x - delta_y;

    draw_circle_field(input, x_end, y_end, thickness/1.5, color);
    while(x_start != x_end || y_start != y_end) {
        draw_circle_field(input, x_start, y_start, thickness/1.5, color);
        second_error = first_error * 2;
        if (second_error > -delta_y) {
            first_error -= delta_y;
            x_start += sign_x;
        }
        if (second_error < delta_x) {
            first_error += delta_x;
            y_start += sign_y;
        }
    }
}

void draw_rectangle(Image* input,
                    int left,
                    int up,
                    int width,
                    int height,
                    Rgb color,
                    int thickness,
                    int fill,
                    Rgb fill_color) {
    int diag = 0;                    
    while (width > 0 && height > 0) {
        if (diag >= thickness) {
            if (fill == 0) break;
            color = fill_color;
        }

        if (diag > 0) {
            left += 1;
            up += 1;
            width -= 2;
            height -= 2;
        }
        for (int x = left; x <= left + width; x++) {
            set_pixel(input, x, up, color);
            set_pixel(input, x, up + height, color);
        }

        for (int y = up; y <= up + height; y++) {
            set_pixel(input, left, y, color);
            set_pixel(input, left + width, y, color);
        }

        diag++;
    }
}

void draw_split(Image* input,
                  int count_x,
                  int count_y,
                  int thickness,
                  Rgb color) {
    int area_y_size = (input->height - thickness * (count_x - 1)) / count_x;
    int y_shift = (input->height - (area_y_size + (count_x - 1) * (thickness + area_y_size))) / 2;
    int area_x_size = (input->width - thickness * (count_y - 1)) / count_y;
    int x_shift = (input->width - (area_x_size + (count_y - 1) * (thickness + area_x_size))) / 2;

    if (area_y_size < 0 || area_x_size < 0) {
        draw_rectangle(input, 0, 0,
                              input->width, input->height,
                              color, 1,
                              1, color);
        return;
    }

    for (int index = 0; index < count_x - 1; index++)
        draw_line(input, color, thickness,
                          0, y_shift + area_y_size + index * (thickness + area_y_size),
                          input->width, y_shift + area_y_size + index * (thickness + area_y_size));
    
    for (int index = 0; index < count_y - 1; index++)
        draw_line(input, color, thickness,
                          x_shift + area_x_size + index * (thickness + area_x_size), 0,
                          x_shift + area_x_size + index * (thickness + area_x_size), input->height);
    
    return;
}

void draw_circle_pixel(Image* input,
                   int x,
                   int y,
                   int size,
                   Rgb color,
                   Rgb circle_color) {
    for (int shift_x = -size; shift_x <= size; shift_x++) {
        for (int shift_y = -size; shift_y <= size; shift_y++) {
            int cursor_x = x + shift_x;
            int cursor_y = y + shift_y;
            if ((0 <= cursor_x) && (0 <= cursor_y) &&
                (cursor_x < input->width) && (cursor_y < input->height)) {
                    Rgb cursor_color = input->pix[cursor_x][cursor_y];
                    if (!cmp_color(cursor_color, color))
                        set_pixel(input, cursor_x, cursor_y, circle_color);
            }
        }
    }
}

void draw_circle_pixels(Image* input,
                   int size,
                   Rgb color,
                   Rgb circle_color) {
    for (int x = 0; x < input->width; x++) {
        for (int y = 0; y < input->height; y++) {
            if (cmp_color(input->pix[x][y], color))
                draw_circle_pixel(input, x, y, size, color, circle_color);
        }
    }
}
