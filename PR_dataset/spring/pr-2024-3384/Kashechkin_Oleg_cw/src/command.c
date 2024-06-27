#include <stdbool.h>
#include "command.h"

int rect(image *img, int start_y, int start_x, int end_y, int end_x, int width, int color[3], bool fill, int color_for_fill[3])
{
    width = width / 2;
    int tmp = end_x;
    end_x = end_y;
    end_y = tmp;

    tmp = start_x;
    start_x = start_y;
    start_y = tmp;

    if (start_x > end_x)
    {
        int temp = end_x;
        end_x = start_x;
        start_x = temp;
    }
    if (start_y > end_y)
    {
        int temp = end_y;
        end_y = start_y;
        start_y = temp;
    }

    for (int y = start_y - width; y <= end_y + width; y++)
    {
        for (int x = start_x - width; x <= end_x + width; x++)
        {
            if (
                ((x - start_x) <= width) || ((y - start_y) <= width) || ((end_x - x) <= width) || ((end_y - y) <= width))
            {
                set_pixel(img, x, y, color);
            }
            else if (fill)
            {
                set_pixel(img, x, y, color_for_fill);
            }
        }
    }
    return 0;
}

int hexagon(image *img, int center_x, int center_y, int radius, int width, int color[3], bool fill, int color_for_fill[3])
{
    // radius = radius + (width / 2);
    // width = width / 2;

    int x_pos[6], y_pos[6];
    for (int i = 0; i < 6; i++)
    {
        x_pos[i] = center_x + radius * cos(2 * PI / 6 * i);
        y_pos[i] = center_y + radius * sin(2 * PI / 6 * i);
    }
    int img_width = img->width;
    int img_height = img->height;

    for (int i = 0; i < 6; i++)
    {
        int next_i = (i + 1) % 6;
        // if (x_pos[i] >= 0 && x_pos[i] < img_width && y_pos[i] >= 0 && y_pos[i] < img_height &&
        //     x_pos[next_i] >= 0 && x_pos[next_i] < img_width && y_pos[next_i] >= 0 && y_pos[next_i] < img_height) {
        draw_line2(img, x_pos[i], y_pos[i], x_pos[next_i], y_pos[next_i], color, width);
        //}
    }

    int fill_x = (x_pos[0] + x_pos[3]) / 2;
    int fill_y = (y_pos[0] + y_pos[3]) / 2;
    if (fill == true)
    {
        if (fill_x >= 0 && fill_x < img_width && fill_y >= 0 && fill_y < img_height)
        {
            flood_fill(img, fill_x, fill_y, color_for_fill, color);
        }
    }
}

int mirror(image *img, char *axis, int start_x, int start_y, int end_x, int end_y)
{
    if (end_x >= img->width)
    {
        end_x = img->width - 1;
    }
    if (end_y >= img->height)
    {
        end_y = img->height - 1;
    }
    if (*(axis) == 'x')
    {
        for (int y = start_y; y <= end_y; y++)
        {
            for (int x = start_x; x <= (start_x + (end_x - start_x) / 2); x++)
            {
                int mirror_x = end_x - (x - start_x);
                unsigned char temp_r = img->data[y][x * 3];
                unsigned char temp_g = img->data[y][x * 3 + 1];
                unsigned char temp_b = img->data[y][x * 3 + 2];
                img->data[y][x * 3] = img->data[y][mirror_x * 3];
                img->data[y][x * 3 + 1] = img->data[y][mirror_x * 3 + 1];
                img->data[y][x * 3 + 2] = img->data[y][mirror_x * 3 + 2];
                img->data[y][mirror_x * 3] = temp_r;
                img->data[y][mirror_x * 3 + 1] = temp_g;
                img->data[y][mirror_x * 3 + 2] = temp_b;
            }
        }
    }
    else if (*(axis) == 'y')
    {
        for (int y = start_y; y <= (start_y + (end_y - start_y) / 2); y++)
        {
            for (int x = start_x; x <= end_x; x++)
            {
                int mirror_y = end_y - (y - start_y);
                unsigned char temp_r = img->data[y][x * 3];
                unsigned char temp_g = img->data[y][x * 3 + 1];
                unsigned char temp_b = img->data[y][x * 3 + 2];
                img->data[y][x * 3] = img->data[mirror_y][x * 3];
                img->data[y][x * 3 + 1] = img->data[mirror_y][x * 3 + 1];
                img->data[y][x * 3 + 2] = img->data[mirror_y][x * 3 + 2];
                img->data[mirror_y][x * 3] = temp_r;
                img->data[mirror_y][x * 3 + 1] = temp_g;
                img->data[mirror_y][x * 3 + 2] = temp_b;
            }
        }
    }
    return 0;
}

int pentagram(image *img, int center_y, int center_x, int radius, int width, int color[3])
{
    for (int y = center_y - radius - width; y <= center_y + radius + width; y++)
    {
        for (int x = center_x - radius - width; x <= center_x + radius + width; x++)
        {
            double distance = sqrt((x - center_x) * (x - center_x) + (y - center_y) * (y - center_y));
            if (fabs(distance - radius) <= (width / 2) && x >= 0 && x < img->width && y >= 0 && y < img->height)
            {
                set_pixel(img, x, y, color);
            }
        }
    }

    double alpha = PI / 5;
    int x[5], y[5];
    for (int i = 0; i < 5; i++)
    {
        x[i] = (center_x - width / 2) + radius * cos(2 * i * alpha + ((3 * PI) / 2));
        y[i] = (center_y - width / 2) + radius * sin(2 * i * alpha + ((3 * PI) / 2));
    }

    for (int i = 0; i < 5; i++)
    {
        int start_x = x[i];
        int start_y = y[i];
        int end_x = x[(i + 2) % 5];
        int end_y = y[(i + 2) % 5];

        // if (start_x >= 0 && start_x < img->width && start_y >= 0 && start_y < img->height &&
        //     end_x >= 0 && end_x < img->width && end_y >= 0 && end_y < img->height) {
        draw_line(img, start_x, start_y, end_x, end_y, color, width);
        // }
    }

    return 0;
}


// int paving(image* img, int start_y, int start_x, int end_y, int end_x) {

//     int tmp = end_x;
//     end_x = end_y;
//     end_y = tmp;

//     tmp = start_x;
//     start_x = start_y;
//     start_y = tmp;

//     if (start_x > end_x)
//     {
//         int temp = end_x;
//         end_x = start_x;
//         start_x = temp;
//     }
//     if (start_y > end_y)
//     {
//         int temp = end_y;
//         end_y = start_y;
//         start_y = temp;
//     }

//     int width = end_x - start_x;
//     int center_y = (end_y + start_y) / 2;
//     int center_x = (end_x + start_x) / 2;
    
//     int x0 = center_x - width/2;
//     int y0 = center_y - width/2;

//     unsigned char **newdata = malloc(sizeof(unsigned char *) * width);
//     for (int i = 0; i < width; i++) {
//         newdata[i] = malloc(3 * width);
//     }

//     for (int y = 0; y < width; y++) {
//         for (int x = 0; x < width; x++) {
//             int color[3];
//             get_pixel(img, x + x0, y + y0, color);
//             newdata[y][x * 3] = color[0];
//             newdata[y][x * 3 + 1] = color[1];
//             newdata[y][x * 3 + 2] = color[2];
//         }
//     }

//     for (int y = 0; y < img->height; y++) {
//         for (int x = 0; x < img->width; x++) {
//             int color[3];
//             color[0] = newdata[y % width][(x % width) * 3];
//             color[1] = newdata[y % width][(x % width) * 3 + 1];
//             color[2] = newdata[y % width][(x % width) * 3 + 2];
//             set_pixel(img, x, y, color);
//         }
//     }

//     return 0;
// }

int paving(image* img, int start_x, int start_y, int end_x, int end_y) {
    int x0 = start_x;
    int y0 = start_y;
    int dx = end_x - start_x;
    int dy = end_y - start_y;
    
    if (dx <= 0 || dy <= 0) {
        printf("bad rect\n");
        exit(40);
    }
    
    unsigned char **newdata = malloc(sizeof(unsigned char *) * dy);
    for (int i = 0; i < dy; i++) {
        newdata[i] = malloc(3 * dx);
    }

    for (int y = 0; y < dy; y++) {
        for (int x = 0; x < dx; x++) {
            int color[3];
            get_pixel(img, x + x0, y + y0, color);
            newdata[y][x * 3] = color[0];
            newdata[y][x * 3 + 1] = color[1];
            newdata[y][x * 3 + 2] = color[2];
        }
    }

    for (int y = 0; y < img->height; y++) {
        for (int x = 0; x < img->width; x++) {
            int color[3];
            color[0] = newdata[y % dy][(x % dx) * 3];
            color[1] = newdata[y % dy][(x % dx) * 3 + 1];
            color[2] = newdata[y % dy][(x % dx) * 3 + 2];
            set_pixel(img, x, y, color);
        }
    }
}


int outside_rect(image *img, int start_y, int start_x, int end_y, int end_x,int color[3]) {
    exit(40);
}