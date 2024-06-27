#ifndef DRAWING_C
#define DRAWING_c

#include "../cwdrawing/cwdrawing.h"

    
static void swap_x(Coord_t *first, Coord_t *second)
{
    Coord_t tmp = *first;
    first->x = second->x;
    second->x = tmp.x;
}

static void swap_y(Coord_t *first, Coord_t *second)
{
    Coord_t tmp = *first;
    first->y = second->y;
    second->y = tmp.y;
}

static void set_area(int width, int height, Coord_t *left_up, Coord_t *right_down)
{
    *left_up = (Coord_t){left_up->x < 0 ? 0 : left_up->x,
                         left_up->y < 0 ? 0 : left_up->y};
    *left_up = (Coord_t){left_up->x >= width ? width : left_up->x,
                         left_up->y >= height ? height : left_up->y};

    *right_down = (Coord_t){right_down->x < 0 ? 0 : right_down->x,
                         right_down->y < 0 ? 0 : right_down->y};
    *right_down = (Coord_t){right_down->x >= width ? width : right_down->x,
                         right_down->y >= height ? height : right_down->y};

    if (right_down->x < left_up->x)
    {
        swap_x(right_down, left_up);
    }

    if (left_up->y > right_down->y)
    {
        swap_y(left_up, right_down);
    }
}

void draw_dot(Bitmap_image_t *image, Coord_t coordinate, RGB_t color)
{
    if (!valid_coordinate(coordinate, image->hdr.width, image->hdr.height))
    {
        return;
    }

    if (!valid_rgb(color))
    {
        throw_error(INVALID_COORDINATE_ERROR_MSG, INVALID_COORDINATE_ERROR_RET_VAL);
    }

    set_pixel(image, coordinate, color);
}

static void draw_horizontal_line(Bitmap_image_t *image, Coord_t start, Coord_t end, RGB_t color)
{
    if (end.y != start.y)
    {
        throw_error(INVALID_DRAWING_COORDINATES_MSG, INVALID_DRAWING_COORDINATES_RET_VAL);
    }

    if (start.y < 0 || start.y >= image->hdr.height)
    {
        return;
    }

    if (start.x > end.x)
    {
        swap_x(&start, &end);
    }

    for (Coord_t current = start; current.x <= end.x; current.x++)
    {
        draw_dot(image, current, color);
    }
}

static void draw_vertical_line(Bitmap_image_t *image, Coord_t start, Coord_t end, RGB_t color)
{
    if (end.x != start.x)
    {
        throw_error(INVALID_DRAWING_COORDINATES_MSG, INVALID_DRAWING_COORDINATES_RET_VAL);
    }

    if (start.x < 0 || start.x >= image->hdr.width)
    {
        return;
    }

    if (start.y > end.y)
    {
        swap_y(&start, &end);
    }

    for (Coord_t current = start; current.y <= end.y; current.y++)
    {
        draw_dot(image, current, color);
    }
}

static bool circle_is_visible(Coord_t center, int radius, int width, int height)
{
    if (center.x + radius < 0)
    {
        return false;
    }

    if (center.y + radius < 0)
    {
        return false;
    }

    if (center.x - radius >= width)
    {
        return false;
    }

    if (center.y - radius >= height)
    {
        return false;
    }

    return true;
}

void fill_circle(Bitmap_image_t *image, Coord_t center, int radius, RGB_t color)
{
    if (radius < 0)
    {
        throw_error(INVALID_DRAWING_COORDINATES_MSG, INVALID_DRAWING_COORDINATES_RET_VAL);
    }

    if (!valid_rgb(color))
    {
        throw_error(INVALID_RGB_ERROR_MSG, INVALID_RGB_ERROR_RET_VAL);
    }

    if (!circle_is_visible(center, radius, image->hdr.width, image->hdr.height))
    {
        return;
    }

    int error = 3 - (2 * radius);

    draw_dot(image, (Coord_t){center.x, center.y + radius}, color);
    draw_dot(image, (Coord_t){center.x, center.y - radius}, color);
    draw_horizontal_line(image, (Coord_t){center.x + radius, center.y},
                                (Coord_t){center.x - radius, center.y}, color);

    for (Coord_t current = {0, radius}; current.x <= current.y; current.x++)
    {
        int vertical_step = 0;
        if (error < 0)
        {
            error += 4 * current.x + 1;
        } 
        else
        {
            current.y--;
            vertical_step = 1;
            error += 4 * (current.x - current.y) + 1;
        }

        if (vertical_step == 1)
        {
            draw_horizontal_line(image, (Coord_t){center.x + current.x, center.y - current.y},
                                        (Coord_t){center.x - current.x, center.y - current.y}, color);
            draw_horizontal_line(image, (Coord_t){center.x + current.x, center.y + current.y},
                                        (Coord_t){center.x - current.x, center.y + current.y}, color);
        }
        else
        {
            draw_dot(image, (Coord_t){center.x + current.x, center.y - current.y}, color);
            draw_dot(image, (Coord_t){center.x - current.x, center.y - current.y}, color);
            draw_dot(image, (Coord_t){center.x + current.x, center.y + current.y}, color);
            draw_dot(image, (Coord_t){center.x - current.x, center.y + current.y}, color);
        }

        if (current.y != current.x)
        {
            draw_horizontal_line(image, (Coord_t){center.x + current.y, center.y - current.x},
                                        (Coord_t){center.x - current.y, center.y - current.x}, color);
            draw_horizontal_line(image, (Coord_t){center.x + current.y, center.y + current.x},
                                        (Coord_t){center.x - current.y, center.y + current.x}, color);  
        }
    }
}

void draw_circle(Bitmap_image_t *image, Coord_t center, int radius, RGB_t color, int rim) {
    if (radius < 0)
    {
        throw_error(INVALID_DRAWING_COORDINATES_MSG, INVALID_DRAWING_COORDINATES_RET_VAL);
    }

    if (!valid_rgb(color))
    {
        throw_error(INVALID_RGB_ERROR_MSG, INVALID_RGB_ERROR_RET_VAL);
    }

    if (!circle_is_visible(center, radius, image->hdr.width, image->hdr.height))
    {
        return;
    }

    int error = 3 - (2 * radius);

    draw_horizontal_line(image, (Coord_t){center.x + radius, center.y},
                                (Coord_t){center.x + radius - rim, center.y}, color);
    draw_vertical_line(image, (Coord_t){center.x, center.y + radius},
                              (Coord_t){center.x, center.y + radius - rim}, color);
    draw_horizontal_line(image, (Coord_t){center.x - radius, center.y},
                                (Coord_t){center.x - radius + rim, center.y}, color);
    draw_vertical_line(image, (Coord_t){center.x, center.y - radius},
                              (Coord_t){center.x, center.y - radius + rim}, color);

    for (Coord_t current = {0, radius}; current.x <= current.y; current.x++)
    {    
        if (error < 0) {
            error += 4 * current.x + 1;
        }
        else
        {
            current.y--;
            error += 4 * (current.x - current.y) + 1;
        }

        draw_horizontal_line(image, (Coord_t){center.x + current.x, center.y + current.y},
                                    (Coord_t){center.x + current.x - rim, center.y + current.y}, color);
        draw_vertical_line(image, (Coord_t){center.x + current.y, center.y + current.x},
                                  (Coord_t){center.x + current.y, center.y + current.x - rim}, color);
        draw_vertical_line(image, (Coord_t){center.x - current.y, center.y + current.x},
                                  (Coord_t){center.x - current.y, center.y + current.x - rim}, color);
        draw_horizontal_line(image, (Coord_t){center.x - current.x, center.y + current.y},
                                    (Coord_t){center.x - current.x + rim, center.y + current.y}, color);
        draw_horizontal_line(image, (Coord_t){center.x - current.x, center.y - current.y},
                                    (Coord_t){center.x - current.x + rim, center.y - current.y}, color);
        draw_vertical_line(image, (Coord_t){center.x - current.y, center.y - current.x},
                                  (Coord_t){center.x - current.y, center.y - current.x + rim}, color);
        draw_vertical_line(image, (Coord_t){center.x + current.y, center.y - current.x},
                                  (Coord_t){center.x + current.y, center.y - current.x + rim}, color);
        draw_horizontal_line(image, (Coord_t){center.x + current.x, center.y - current.y},
                                    (Coord_t){center.x + current.x - rim, center.y - current.y}, color);
    }
}

void draw_line(Bitmap_image_t *image, Coord_t start, Coord_t end, RGB_t color, int thickness)
{
    if (thickness < 0)
    {
        throw_error(INVALID_COORDINATE_ERROR_MSG, INVALID_COORDINATE_ERROR_RET_VAL);
    }

    int delta_x = abs(end.x - start.x);
    int delta_y = -abs(end.y - start.y);

    int step_x = end.x > start.x ? 1 : -1;
    int step_y = end.y > start.y ? 1 : -1;

    int error = delta_x + delta_y;

    Coord_t current = start;
    while (1)
    {
        if (thickness == 1)
        {
            draw_dot(image, current, color);
        }
        else
        {
            draw_circle(image, current, thickness/2, color, 2);
        }

        if (current.x == end.x && current.y == end.y)
        {
            break;
        }

        if (2 * error >= delta_y)
        {
            if (current.x == end.x)
            {
                break;
            }
            error += delta_y;
            current.x += step_x; 
        }
        if (2 * error <= delta_x)
        {
            if (current.y == end.y)
            {
                break;
            }
            error += delta_x;
            current.y += step_y;
        }
    }

    fill_circle(image, start, thickness/2, color);
    fill_circle(image, end, thickness/2, color);
}

static RGB_t invert_color(RGB_t color)
{
    if (!valid_rgb(color))
    {
        throw_error(INVALID_COORDINATE_ERROR_MSG, INVALID_COORDINATE_ERROR_RET_VAL);
    }

    RGB_t inverted = {0xFF - color.r, 0xFF - color.g, 0xFF - color.b};
    return inverted;
}

void invert_dot(Bitmap_image_t *image, Coord_t coordinate)
{
    if (!valid_coordinate(coordinate, image->hdr.width, image->hdr.height))
    {
        return;
    }

    set_pixel(image, coordinate, invert_color(get_pixel(image, coordinate)));
}

static void invert_horizontal_line(Bitmap_image_t *image, Coord_t start, Coord_t end)
{
    if (end.y != start.y)
    {
        throw_error(INVALID_COORDINATE_ERROR_MSG, INVALID_DRAWING_COORDINATES_RET_VAL);
    }

    if (start.y < 0 || start.y >= image->hdr.height)
    {
        return;
    }

    if (start.x > end.x)
    {
        swap_x(&start, &end);
    }

    for (Coord_t current = start; current.x <= end.x; current.x++)
    {
        invert_dot(image, current);
    }
}

void invert_circle(Bitmap_image_t *image, Coord_t center, int radius)
{
    if (radius < 0)
    {
        throw_error(INVALID_COORDINATE_ERROR_MSG, INVALID_COORDINATE_ERROR_RET_VAL);
    }

    if (!circle_is_visible(center, radius, image->hdr.width, image->hdr.height))
    {
        return;
    }

    int error = 3 - (2 * radius);

    invert_dot(image, (Coord_t){center.x, center.y + radius});
    invert_dot(image, (Coord_t){center.x, center.y - radius});
    invert_horizontal_line(image, (Coord_t){center.x + radius, center.y},
                                  (Coord_t){center.x - radius, center.y});

    for (Coord_t current = {0, radius}; current.x < current.y; current.x++)
    {
        int vertical_step = 0;

        if (error < 0)
        {
            error += 4 * current.x + 1;
        }
        else
        {
            current.y--;
            vertical_step = 1;
            error += 4 * (current.x - current.y) + 1;
        }

        if (vertical_step == 1)
        {
            invert_horizontal_line(image, (Coord_t){center.x + current.x, center.y - current.y},
                                          (Coord_t){center.x - current.x, center.y - current.y});
            invert_horizontal_line(image, (Coord_t){center.x + current.x, center.y + current.y},
                                          (Coord_t){center.x - current.x, center.y + current.y});
        }
        else
        {
            invert_dot(image, (Coord_t){center.x + current.x, center.y - current.y});
            invert_dot(image, (Coord_t){center.x - current.x, center.y - current.y});
            invert_dot(image, (Coord_t){center.x + current.x, center.y + current.y});
            invert_dot(image, (Coord_t){center.x - current.x, center.y + current.y});
        }

        if (current.y != current.x)
        {
            invert_horizontal_line(image, (Coord_t){center.x + current.y, center.y - current.x},
                                          (Coord_t){center.x - current.y, center.y - current.x});
            invert_horizontal_line(image, (Coord_t){center.x + current.y, center.y + current.x},
                                          (Coord_t){center.x - current.y, center.y + current.x});  
        }
    }
}

void crop(Bitmap_image_t *image, Coord_t left_up, Coord_t right_down)
{ 
    set_area(image->hdr.width, image->hdr.height, &left_up, &right_down);

    int new_height = right_down.y - left_up.y; 
    int new_width = right_down.x - left_up.x; 
 
    int old_width = image->hdr.width;
    int old_height = image->hdr.height;
    image->hdr.width = new_width; 
    image->hdr.height = new_height; 
 
    int new_padding = get_padding(new_width); 

    image->data_size = new_height * (new_width * sizeof(RGB_t) + new_padding); 
    image->hdr.image_size = image->data_size;
    image->hdr.file_size = image->data_size + sizeof(Bitmap_header_t); 
 
    unsigned char *new_data = (unsigned char *)calloc(image->data_size, sizeof(unsigned char)); 
    for (int row = 0; row < new_height; row++)
    { 
        memcpy(new_data + get_position((Coord_t){0, row}, new_width, new_height), 
               image->data + get_position((Coord_t){left_up.x, left_up.y + row}, old_width, old_height), 
               new_width * sizeof(RGB_t)); 
    } 
 
    free(image->data); 
    image->data = new_data; 
}

static unsigned char get_contrast_component(unsigned char comp, float alpha, int beta)
{
    int new_comp = (int)(comp * alpha + beta);
    if (new_comp > 255)
    {
        new_comp = 255;
    }
    else if (new_comp < 0)
    {
        new_comp = 0;
    }

    return (unsigned char)new_comp;
}

void contrast(Bitmap_image_t *image, float alpha, int beta) 
{
    if (fabs(alpha) < 0.000001)
    {
        throw_error("OOPs\n", 40);
    }

    int width = image->hdr.width;
    int height = image->hdr.height;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            RGB_t old_color = get_pixel(image, (Coord_t){x, y});

            unsigned char new_red = get_contrast_component(old_color.r, alpha, beta);
            unsigned char new_green = get_contrast_component(old_color.g, alpha, beta);
            unsigned char new_blue = get_contrast_component(old_color.b, alpha, beta);

            RGB_t new_color = {new_red, new_green, new_blue};

            draw_dot(image, (Coord_t){x, y}, new_color);
        }
    }
}

static RGB_t blur_pixel(Bitmap_image_t *image, Coord_t coord, int radius)
{
    RGB_t sum = {0, 0, 0};

    for (int y = -radius + 1; y <= radius; y++)
    {
        for (int x = -radius + 1; x <= radius; x++)
        {   
            Coord_t neighbor_coord = {coord.x + x, coord.y + y};
            if (valid_coordinate(neighbor_coord, image->hdr.width, image->hdr.height))
            {
                sum.r += get_pixel(image, neighbor_coord).r;
                sum.g += get_pixel(image, neighbor_coord).g;
                sum.b += get_pixel(image, neighbor_coord).b; 
            }
        }
    }

    sum.r /= (2 * radius + 1) * (2 * radius + 1);
    sum.g /= (2 * radius + 1) * (2 * radius + 1);
    sum.b /= (2 * radius + 1) * (2 * radius + 1);

    return sum;
}

void blur(Bitmap_image_t *image, int size)
{
    RGB_t **blurred = (RGB_t **)malloc(image->hdr.height * sizeof(RGB_t *));
    for (int i = 0; i < image->hdr.height; i++)
    {
        blurred[i] = (RGB_t *)malloc(image->hdr.width * sizeof(RGB_t));
    }

    for (int y = 0; y < image->hdr.height; y++)
    {
        for (int x = 0; x < image->hdr.width; x++)
        {
            blurred[y][x] = blur_pixel(image, (Coord_t){x, y}, size / 2);
        }
    }

    for (int y = 0; y < image->hdr.height; y++)
    {
        for (int x = 0; x < image->hdr.width; x++)
        {
            draw_dot(image, (Coord_t){x, y}, blurred[y][x]);
        }
    }

    for (int i = 0; i < image->hdr.height; i++)
    {
        if (blurred[i] != NULL)
        {
            free(blurred[i]);
        }
    }
    if (blurred != NULL)
    {
        free(blurred);
    }
}


#endif